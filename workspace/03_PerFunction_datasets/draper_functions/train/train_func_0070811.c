count_tps(flis)
FILE *flis;
{
   int nids;
   char line[MAXLINE];

   nids = 0;

   while(!feof(flis) && fgets(line, MAXLINE, flis) != NULL &&
	 strlen(line) > 2)
   {
      if (line[0] != '>' && strstr(line, "/") == NULL &&
	  strstr(line,"\\") == NULL && strstr(line, ":") == NULL)
      {
	 nids++;
      }
   }
    return (nids);
}
