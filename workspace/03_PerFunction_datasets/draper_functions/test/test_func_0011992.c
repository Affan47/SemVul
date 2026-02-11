lexQString (char *str)
{
  int len = strlen (str) - 1;
  char *dest;
  int z;
  struct qstring *res = (struct qstring *) xmalloc (sizeof (struct qstring));
  res->str = xmalloc (len + 1);
  dest = res->str;

  if (qstringList == NULL)
    {
      res->next = NULL;
      res->prev = NULL;
    }
  else
    {
      res->next = qstringList;
      qstringList->prev = res;
      res->prev = NULL;
    }
  qstringList = res;

  for (z = 0; z < len; z++)
    {
      if (str[z] == '\\')
	{
	  z++;
	  if (z < len)
	    {
	      switch (str[z])
		{
		case '\n':
		  break;
		case 'n':
		  *(dest++) = '\n';
		  break;
		case 't':
		  *(dest++) = '\t';
		  break;
		case 'r':
		  *(dest++) = '\r';
		  break;
		case '"':
		  *(dest++) = '"';
		  break;
		case '\\':
		  *(dest++) = '\\';
		  break;
		default:
		  *(dest++) = '\\';
		  *(dest++) = str[z];
		  break;
		}
	    }
	}
      else
	{
	  *(dest++) = str[z];
	}
    }
  *(dest) = '\0';
  return res;
}
