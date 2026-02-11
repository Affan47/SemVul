expandlst(n)
int n;
{
    FILE *lf, *fopen();
    char buf[100];
    int x;
    char *p = lst[n]+1;
    char *makefnam();

    if(*p)
    {	 makefnam(p,".CMD",buf);
	 upper(buf);
	 if(!(lf=fopen(buf,"r")))
	      arcdie("Cannot read list of files in %s",buf);
    }
    else lf = stdin;

    for(x=n+1; x<lnum; x++)
	 lst[x-1] = lst[x];
    lnum--;

    while(fscanf(lf,"%99s",buf)>0)
    {	 if(!(lst=(char **) realloc(lst,(lnum+1)*sizeof(char *))))
	      arcdie("too many file references");

	 lst[lnum] = malloc(strlen(buf)+1);
	 strcpy(lst[lnum],buf);
	 lnum++;
    }

    if(lf!=stdin)
	 fclose(lf);
}
