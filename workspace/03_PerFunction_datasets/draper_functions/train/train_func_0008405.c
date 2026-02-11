_FP_strpbrk (char *str, char *accept)
{
  char *ptr;

  if (str == NULL)
    return NULL;
  if (accept == NULL || *accept == '\0')
    return str;

  for (; *str; str++)
    for (ptr=accept; *ptr; ptr++)
      if (*str == *ptr)
	return str;

  return NULL;
}
