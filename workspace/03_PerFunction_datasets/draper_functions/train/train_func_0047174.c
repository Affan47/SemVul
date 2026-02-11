hear(int fd, char ** msg)
{
	char * lout = (char *)malloc(81);
	int i=0;
	char c;
	while(1)
	{
		int e=read(fd, &c, 1);
		if(e<1)
			c='\n';
		if(c!=0)
		{
			lout[i++]=c;
			if((i%80)==0)
			{
				if((lout=(char *)realloc(lout, i+81))==NULL)
				{
					printf("\nNot enough memory to store input!\n");
					free(lout);
					*msg=NULL;
					return(-1);
				}
			}
		}
		if(c=='\n')
			break;
	}
	lout[i]=0;
	char *nlout=(char *)realloc(lout, i+1);
	if(nlout==NULL)
	{
		*msg=lout;
		return(1);
	}
	*msg=nlout;
	return(0);
}
