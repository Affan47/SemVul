AppendLinesFromFile(struct Item **filestart,char *filename)

{ FILE *fp;
  char buffer[CF_BUFSIZE];

 if ((fp=fopen(filename,"r")) == NULL)
    {
    snprintf(OUTPUT,CF_BUFSIZE,"Editfiles could not read file %s\n",filename);
    CfLog(cferror,OUTPUT,"fopen");
    return false;
    }

 while (!feof(fp))
    {
    buffer[0] = '\0';
    fgets(buffer,CF_BUFSIZE-1,fp);
    Chop(buffer);
    if (!IsItemIn(*filestart,buffer))
       {
       AppendItem(filestart,buffer,NULL);
       }
    }

 fclose(fp);
 return true;
}
