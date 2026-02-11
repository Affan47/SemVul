content_type_new(const char *content_type_str)
{
  hpair_t *pair = NULL, *last = NULL;
  content_type_t *ct;
  char ch, key[256], value[256];
  int inQuote = 0, i = 0, c = 0, begin = 0, len;
  int mode = 0;


  ct = (content_type_t *) malloc(sizeof(content_type_t));
  ct->params = NULL;

  len = strlen(content_type_str);
  while (i <= len)
  {
    if (i != len)
      ch = content_type_str[i++];
    else
    {
      ch = ' ';
      i++;
    }

    switch (mode)
    {
    case 0:

      if (ch == ';')
      {
        ct->type[c] = '\0';
        c = 0;
        mode = 1;
      }
      else if (ch != ' ' && ch != '\t' && ch != '\r')
        ct->type[c++] = ch;
      break;

    case 1:

      if (ch == '=')
      {
        key[c] = '\0';
        c = 0;
        mode = 2;
      }
      else if (ch != ' ' && ch != '\t' && ch != '\r')
        key[c++] = ch;
      break;

    case 2:

      if (ch != ' ')
        begin = 1;

      if ((ch == ' ' || ch == ';') && !inQuote && begin)
      {
        value[c] = '\0';

        pair = hpairnode_new(key, value, NULL);
        if (ct->params == NULL)
          ct->params = pair;
        else
          last->next = pair;
        last = pair;

        c = 0;
        begin = 0;
        mode = 1;
      }
      else if (ch == '"')
        inQuote = !inQuote;
      else if (begin && ch != '\r')
        value[c++] = ch;

      break;

    }
  }

  return ct;
}
