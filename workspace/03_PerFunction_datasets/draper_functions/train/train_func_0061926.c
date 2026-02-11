parse_attribute_value(parser_t * p)
  {
  char * ret;
  char * end = NULL;
  char close_seq[3];

  if(!p->buffer_size)
    {
    if(!more_data(p))
      return NULL;
    }
  if((p->buffer[0] == '\\') && (p->buffer[1] == '"'))
    {
    close_seq[0] = p->buffer[0];
    close_seq[1] = p->buffer[1];
    close_seq[2] = '\0';
    advance(p, 2);
    }
  else
    {
    close_seq[0] = *(p->buffer);
    close_seq[1] = '\0';
    if((close_seq[0] != '\'') && (close_seq[0] != '"'))
      return NULL;
    advance(p, 1);
    }

  while(1)
    {
    end = strstr(p->buffer, close_seq);

    if(end)
      break;
    if(!more_data(p))
      break;
    }


  if(!end)
    return NULL;
  ret = bgav_strndup(p->buffer, end);

  advance(p, (int)(end - p->buffer) + strlen(close_seq));
  return ret;
  }
