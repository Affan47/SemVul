g_strdup(char const*str) {
  char *t=(char*)NULLP;
  if (str!=NULLP) strcpy(t=(char*)g_malloc(strlen(str)+1),str);
  return t;
}
