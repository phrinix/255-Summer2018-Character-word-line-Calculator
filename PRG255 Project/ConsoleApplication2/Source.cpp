

#include <stdio.h>
#include<string.h>

typedef struct
{
	char word[40];
	int repeat;
}word_arry;

void lower_case(char item[40]);
void couting();
int sorting(word_arry words[1000]);
void output(word_arry words[1000], int n);

void main()
{
	int n;
	word_arry words[1000];
	couting();
	n = sorting(words);

	printf("\nSorted List\n\n");
	for (int i =0; i < n; i++)
	{
		printf("%-20s %d\n", words[i].word, words[i].repeat);
	}
	output(words,n);
	getchar();
	getchar();
}

void lower_case(char item[30])
{
	if (item[0] > 64 && item[0] < 91)
		item[0] += 32;
}

void couting ()
{
	FILE *fp = fopen("data.txt","r");
	int lines = 0, word = 0, characters = 0;
	char chr;
	while ((chr = getc(fp)) != EOF)
	{
		if (chr == ' ')
			word++;
		if (chr == '\n')
			lines ++;
		if (chr != '\n')
			characters++;
	}
	printf("Number of character = %d\n", characters);
	printf("Number of Words = %d\n", (word+lines+1));
	printf("Number of Lines = %d\n", lines+1);
	fclose(fp);

}

int sorting(word_arry words[1000])
{
	char item[40], temp[40];
	int n=0,b=0,temp_n;
	FILE *fp = fopen("data.txt","r");
	rewind(fp);
	while(fscanf(fp,"%s",item) != EOF)
	{
		lower_case(item);
		if(n == 0)
		{
			strcpy(words[n].word,item);
			words[n].repeat = 1;
		}
		else
		{
			for(int i2=0; i2<n; i2++)
			{
				if (strcmp(words[i2].word,item) == 0)
				{
					words[i2].repeat += 1;
					b=1;
					n--;
				}
			}
			if(b == 0)
			{
				strcpy(words[n].word,item);
				words[n].repeat = 1;
			}
		}
		b=0;
		n++;
	}
	
	for (int i =0; i < n; i++)
	{
		for (int j = 1; j<(n-i); j++)
		{
			if (strcmp(words[j-1].word,words[j].word) > 0)
			{
				strcpy(temp,words[j-1].word);
				temp_n = words[j-1].repeat;
				strcpy(words[j-1].word,words[j].word);
				words[j-1].repeat = words[j].repeat;
				strcpy(words[j].word,temp);
				words[j].repeat = temp_n;
			}
		}
	}
	fclose(fp);
	return n;
}

void output(word_arry words[1000], int n)
{
	FILE *fp = fopen("output.txt","w");
	for(int i = 0; i < n; i++)
	fprintf(fp,"%-20s %d\n", words[i].word,words[i].repeat);

	fclose(fp);
}