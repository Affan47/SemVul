print_class_(FILE *fp, int tab1, int tab2, char *flag)
{
     int	i, j, n;

     for (i = 1; (Class[i][0].id != NULL) && (i < CLASSIFY_NO); i++) {
	  if (tab1 > 0) for (n = 0; n < tab1; n++) fputc(' ', fp);
	  fprintf(fp, "%3d: %s", i, Class[i][0].id);
	  if (Class[i][0].kt) fputs(flag, fp);
	  fputc('\n', fp);
	  for (j = 1; (Class[i][j].id != NULL) && (j < CLASSIFY_NO); j++) {
	       if (tab2 > 0) for (n = 0; n < tab2; n++) fputc(' ', fp);
	       fprintf(fp, "        %3d: %s", j, Class[i][j].id);
	       if (Class[i][j].kt) fputs(flag, fp);
	       fputc('\n', fp);
	  }
     }
}
