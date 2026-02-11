find_fmtp(char ** fmtp, char * key)
  {
  int i = 0;
  char * pos;
  int len;
  while(fmtp[i])
    {
    pos = fmtp[i];
    while(isspace(*pos))
      pos++;
    len = strlen(key);
    if(!strncasecmp(key, pos, len) &&
       (pos[len] == '='))
      {
      pos += len+1;
      while(isspace(*pos))
        pos++;
      return pos;
      }
    i++;
    }
  return NULL;
  }
