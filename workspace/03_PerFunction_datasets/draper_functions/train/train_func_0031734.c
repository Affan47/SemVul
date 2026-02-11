qs_man_print(int man, const char *fmt, ...) {
  char bufin[4096];
  char bufout[4096];
  va_list args;
  int i = 0;
  int j = 0;
  memset(bufin, 0, 4096);
  va_start(args, fmt);
  vsprintf(bufin, fmt, args);
  if(man) {


    while(bufin[i] == ' ') {
      i++;
    }
  }
  while(bufin[i] && j < 4000) {

    if(man && (bufin[i] == '\\' || bufin[i] == '-')) {
      bufout[j] = '\\';
      j++;
    }
    if(bufin[i] == '\n') {
      if(man) {

	i++;
      } else {

	bufout[j] = bufin[i];
	i++;
	j++;
      }
    } else {

      bufout[j] = bufin[i];
      i++;
      j++;
    }
  }
  bufout[j] = '\0';
  printf("%s", bufout);
  if(man) {
    printf(" ");
  }
}
