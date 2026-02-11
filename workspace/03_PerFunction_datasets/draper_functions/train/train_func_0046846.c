process_configfile(const string configfile)
{
  char line[MAXLINELEN], chapter[MAXLINELEN];
  FILE *f;

  if (! (f = fopenurl(configfile, "r", NULL))) {perror(configfile); exit(2);}


  while (fgets(line, sizeof(line), f)) {
    if (sscanf(line, " @chapter %s", chapter) == 1) {
      if (!base) base = chapter;
      yyin = fopenurl(chapter, "r", NULL);
      if (yyin == NULL) {perror(chapter); exit(2);}
      if (yyparse() != 0) exit(3);
      fclose(yyin);
      base = NULL;
    }
  }

  fclose(f);
}
