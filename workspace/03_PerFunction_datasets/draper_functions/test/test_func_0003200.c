strip_dir(char *s){
  int i, first = TRUE;
  for (i = strlen(s); i >= 0; i--) {
    if (first && s[i] == '.') {
      s[i] = '\0';
      first = FALSE;
    }
    if (s[i] == '/') return (char*) &(s[i+1]);
  }
  return s;
}
