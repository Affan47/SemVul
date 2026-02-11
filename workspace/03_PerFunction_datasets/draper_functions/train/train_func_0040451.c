__gnat_getenv (char *name, int *len, char **value)
{
  *value = getenv (name);
  if (!*value)
    *len = 0;
  else
    *len = strlen (*value);

  return;
}
