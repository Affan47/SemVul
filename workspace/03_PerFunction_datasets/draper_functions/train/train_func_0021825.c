httpGetSubField2(http_t       *http,
                 http_field_t field,
                 const char   *name,
		 char         *value,
		 int          valuelen)
{
  const char	*fptr;
  char		temp[HTTP_MAX_VALUE],
		*ptr,
		*end;

  DEBUG_printf(("httpGetSubField2(http=%p, field=%d, name=\"%s\", value=%p, valuelen=%d)\n",
                http, field, name, value, valuelen));

  if (!http || !name || !value || valuelen < 2 ||
      field <= HTTP_FIELD_UNKNOWN || field >= HTTP_FIELD_MAX)
    return (NULL);

  end = value + valuelen - 1;

  for (fptr = http->fields[field]; *fptr;)
  {


    while (isspace(*fptr & 255))
      fptr ++;

    if (*fptr == ',')
    {
      fptr ++;
      continue;
    }


    for (ptr = temp;
         *fptr && *fptr != '=' && !isspace(*fptr & 255) &&
	     ptr < (temp + sizeof(temp) - 1);
         *ptr++ = *fptr++);

    *ptr = '\0';

    DEBUG_printf(("httpGetSubField: name=\"%s\"\n", temp));


    while (isspace(*fptr & 255))
      fptr ++;

    if (!*fptr)
      break;

    if (*fptr != '=')
      continue;


    fptr ++;

    while (isspace(*fptr & 255))
      fptr ++;

    if (*fptr == '\"')
    {


      for (ptr = value, fptr ++;
           *fptr && *fptr != '\"' && ptr < end;
	   *ptr++ = *fptr++);

      *ptr = '\0';

      while (*fptr && *fptr != '\"')
        fptr ++;

      if (*fptr)
        fptr ++;
    }
    else
    {


      for (ptr = value;
           *fptr && !isspace(*fptr & 255) && *fptr != ',' && ptr < end;
	   *ptr++ = *fptr++);

      *ptr = '\0';

      while (*fptr && !isspace(*fptr & 255) && *fptr != ',')
        fptr ++;
    }

    DEBUG_printf(("httpGetSubField: value=\"%s\"\n", value));


    if (!strcmp(name, temp))
      return (value);
  }

  value[0] = '\0';

  return (NULL);
}
