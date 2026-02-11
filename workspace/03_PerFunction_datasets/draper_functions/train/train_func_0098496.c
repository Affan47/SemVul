find_chars(parser_t * p, const char * chars)
  {
  char * pos = NULL;
  while(1)
    {
    pos = strpbrk(p->buffer, chars);
    if(pos)
      return pos;
    if(!more_data(p))
      break;
    }
  return NULL;
  }
