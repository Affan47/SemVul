is_a_number(gchar *string)
{
  gchar *tmp;

  if (string == NULL)
    return FALSE;
  tmp = string;
  while (*tmp)
    {

      if ((*tmp < '0' ||
	   *tmp > '9') &&
	  *tmp != ' ' &&
	  *tmp != '.')
	return FALSE;
      tmp ++;
    }
  return TRUE;
}
