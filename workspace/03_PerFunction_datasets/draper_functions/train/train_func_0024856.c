mjg_strdup(const char *s, const char * const file, const int line)
{
  if(NULL == s) {
    return NULL;
  }

  {
    char *dup = mjg_realloc(NULL,(long)(strlen(s) + 1), sizeof(char),file,line);
    if((dup != NULL) && (s != NULL)) {
      strcpy(dup, s);
    } else {
      fprintf(stderr, "mjg_strdup: ERROR: mjg_realloc failed\n");
    }
    return dup;
  }
}
