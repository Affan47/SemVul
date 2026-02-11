dump_string(const char * str, int len)
  {
  int  i;
  for(i = 0; i < len; i++)
    fputc(str[i], stderr);
  }
