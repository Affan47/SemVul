_ppdGetLanguages(ppd_file_t *ppd)
{
  cups_array_t	*languages;
  ppd_attr_t	*attr;
  char		*value,
		*start,
		*ptr;


  if ((attr = ppdFindAttr(ppd, "cupsLanguages", NULL)) == NULL || !attr->value)
    return (NULL);


  if ((languages = cupsArrayNew((cups_array_func_t)strcmp, NULL)) == NULL)
    return (NULL);

  if ((value = strdup(attr->value)) == NULL)
  {
    cupsArrayDelete(languages);
    return (NULL);
  }

  for (ptr = value; *ptr;)
  {


    while (_cups_isspace(*ptr))
      ptr ++;

    if (!*ptr)
      break;


    for (start = ptr; *ptr && !_cups_isspace(*ptr); ptr ++);

    if (*ptr)
      *ptr++ = '\0';

    if (!strcmp(start, "en"))
      continue;

    cupsArrayAdd(languages, strdup(start));
  }


  free(value);

  if (cupsArrayCount(languages) == 0)
  {
    cupsArrayDelete(languages);
    return (NULL);
  }
  else
    return (languages);
}
