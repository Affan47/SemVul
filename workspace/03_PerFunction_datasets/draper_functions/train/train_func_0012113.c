template_name_p (tree name)
{
  const char *ptr = IDENTIFIER_POINTER (name);
  while (*ptr && *ptr != '<')
    ptr++;

  return *ptr != '\0';
}
