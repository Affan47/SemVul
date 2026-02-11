qs_tail(const char *cmd, FILE *f, const char *pattern) {
  char *cont = NULL;
  long search_win_len = (strlen(pattern) * 2) + 32;
  char line[search_win_len + 10];
  long pos = 0;
  size_t len;
  char *startpattern = NULL;
  fseek(f, 0L, SEEK_END);
  pos = ftell(f);
  while(pos > search_win_len) {
    int offset = 0;
    pos = pos - (search_win_len/2);
    fseek(f, pos, SEEK_SET);
    len = fread(&line, 1, search_win_len, f);
    if(len <= 0) {

      return 1;
    }
    line[len] = '\0';
    if((startpattern = strstr(line, pattern)) != NULL) {
      int containsend = 0;
      char *s = startpattern;
      char *end;
      offset = startpattern - line;

      while((s > line) && (s[0] != CR) && (s[0] != LF)) {
        s--;
      }
      if((s[0] != CR) && (s[0] != LF)) {

        qs_readline(pos, f);
      }
      s++;
      end = startpattern;

      while((offset < search_win_len) && end[0] && end[0] != CR && end[0] != LF) {
        end++;
        offset++;
      }

      if((end[0] == CR) || (end[0] == LF)) {
        end[0] = '\0';
        printf("%s\n", s);
        containsend = 1;
      } else {
        printf("%s", s);
      }
      fseek(f, pos + offset, SEEK_SET);
      if(containsend) {

        cont = fgets(line, sizeof(line), f);
      } else {
        cont = line;
      }
      if(cont) {
        while(fgets(line, sizeof(line), f) != NULL) {
          printf("%s", line);
        }
      }
      return 0;
    }
  }
  return 1;
}
