get_attribute_index(char *s)
{
  int i, found;

  if (str_ident(s, ""))
    return(-1);
  else {
    for (i = 0, found = 0; i < MAX_ATTRIBUTES && !found; i++)
      found = str_ident(s, Attributes[i].name);
    return(found ? i-1 : -1);
  }
}
