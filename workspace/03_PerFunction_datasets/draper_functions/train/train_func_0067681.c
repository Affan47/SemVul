find_string(const char * buf, char **string)
  {
  int i;
  char *ptr;
  ptr = (char*)buf;

  while(!isspace(*ptr))
    {
    if(*ptr == '\0')
      return 0;
    ptr++;
    }
  ptr++;

  while(!isdigit(*ptr))
    {
    if(*ptr == '\0')
      return 0;
    ptr++;
    }

  i = atoi(ptr);

  *string = calloc(i+1, sizeof(char));

  while(!isspace(*ptr))
    {
    if(*ptr == '\0')
      return 0;
    ptr++;
    }
  ptr++;

  strncpy(*string, ptr, i);
  return 1;
  }
