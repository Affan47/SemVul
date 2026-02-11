format_string(char *s) {
  char *new_s, *new_s_corrected;
  int i, j;
  ALLOCS(new_s, strlen(s)*2 + 3);
  new_s[0] = '\"';
  for(i = 0, j = 1; i < strlen(s); i++, j++) {
    switch(s[i]) {
      case '\"': new_s[j] = '\\'; j++; new_s[j] = '\"'; break;
      case '\\': new_s[j] = '\\'; j++; new_s[j] = '\\'; break;
      case '\t': new_s[j] = '\\'; j++; new_s[j] = 't'; break;
      case '\n': new_s[j] = '\\'; j++; new_s[j] = 'n'; break;
      default: new_s[j] = s[i];
    }
  }
  new_s[j] = '\"';
  new_s[j + 1] = 0;
  ALLOCS(new_s_corrected, strlen(new_s) + 1);
  strcpy(new_s_corrected, new_s);
  free(new_s);
  return new_s_corrected;
}
