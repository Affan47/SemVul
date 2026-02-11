main(int argc, char *argv[])
{
	if(argv[1] == NULL || argv[2] == NULL)
	{
		printf("No Makefile / Variable given as parameter(s)\n");
		return(1);
	}


	FILE *f = fopen(argv[1],"r");
	FILE *o = fopen("Makefile.new","w");
	while(!feof(f))
	{
		char line[300000];
		memset((char*)&line,0,300000);
		if(fgets((char*)&line,300000,f)==NULL)
			break;

		if(strstr((char*)&line,argv[2]) == (char*)&line)
		{
			int count = 0;


			char *tok;
			tok = strtok ((char*)&line," =\n");
			int i = 0;
			while (tok != NULL)
			{

				if(i == 1)
					count = atoi(tok);
				tok = strtok (NULL," =\n");
				i++;
			}

			count++;


			fprintf(o,"%s = %d\n",argv[2],count);
		}
		else
			fprintf(o,"%s",&line);
	}
	fclose(f);
	fclose(o);
	remove(argv[1]);
	rename("Makefile.new",argv[1]);
	return (0);
}
