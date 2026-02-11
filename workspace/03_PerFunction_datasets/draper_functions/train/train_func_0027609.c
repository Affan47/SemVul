getfile(line, filepath, seqname)
char *line, *filepath, *seqname;
{
   FILE *fp;
   char *ptr, ctemp[FNAMELEN];

   fp = NULL;
   seqname[0] = '\0';

   if (strstr(line, "/") != NULL || strstr(line, ":") != NULL)
   {
	ptr = strtok(line, " \n\t\r");
	strcpy(filepath, ptr);
   }

   else if (line[0] != '>')
   {
	ptr = strtok(line, " \n\t\r");
	if (ptr != NULL)
	{
		if ((int) strlen(ptr) > SNAMELEN - 1) ptr[SNAMELEN - 1] = '\0';
		strcpy(seqname, ptr);
		strcpy(ctemp, filepath);
		strcat(ctemp, seqname);
		strcat(ctemp, PROTEIN_EXTENSION);
		if ( (fp = fopen(ctemp, READ) ) == NULL)
			printf("***%s not found\n", ctemp);
	}
   }

   return(fp);
}
