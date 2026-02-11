search_file(FILE *cmd, int num, char *str) {

  int replace, count, temp;
  char line[BIG_LINE];
  char **buffer = NULL;
  char **tmp = NULL;
  int i = 0;

  if(num <= 0) return;

  replace=0;
  count=0;
  while(fgets(line, sizeof(line), cmd)) {
    if(strncmp(line, "format=", 7))
      if((!str) || (strstr(line, str))) {
        count++;
        if(count<=num) {
          if(!buffer) {
            buffer = (char **)MALLOC(sizeof(char *));
            if (!buffer) {

              return;
            }
          } else {
            tmp = (char **)REALLOC(buffer, count*(sizeof(char *)));
            if (!tmp) {

              for (i=0; i<(count-1); i++) {
                FREE(buffer[i]);
              }
              FREE(buffer);
              return;
            }
            buffer = tmp;
          }
        } else {
          FREE(buffer[replace]);
        }

        temp = strlen(line);
        line[temp-1] = ' ';
        line[temp] = '\n';
        line[temp+1] = '\0';
        buffer[replace] = STRDUP(line);
        if(replace == (num-1))
          replace=0;
        else replace++;
      }
  }
  if(count < num) {
    replace=0;
  }
  else count=num;


  for(temp=0; temp<count; temp++) {
    fputs(buffer[replace], stdout);
    FREE(buffer[replace]);
    if(replace == (num-1))
      replace=0;
    else replace++;
  }
  if(buffer)
    FREE(buffer);
}
