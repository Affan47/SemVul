char_in_list(int ch, char *list)
{
  char *p;

  for(p = list; *p != '\0'; p++)
    if (*p == ch) return TRUE;

  return FALSE;
}
