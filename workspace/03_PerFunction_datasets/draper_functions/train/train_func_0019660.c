opt_kanji(Jconf *jconf, char *arg[], int argnum)
{
#ifdef CHARACTER_CONVERSION
  if (from_code) free(from_code);
  if (to_code) free(to_code);
  from_code = NULL;
  if (!strcmp(arg[0], "noconv")) {
    to_code = NULL;
  } else {
    to_code = strcpy((char*)mymalloc(strlen(arg[0])+1),arg[0]);
  }
#else
  fprintf(stderr, "Warning: character set conversion disabled, option \"-kanji\" ignored\n");
#endif
  return TRUE;
}
