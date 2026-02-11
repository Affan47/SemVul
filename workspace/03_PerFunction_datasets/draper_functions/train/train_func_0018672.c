atBindTestRule (name)
     char *name;
{
  int i;
  char *parenthPtr = strchr (name, '(');

  atBindInitRules ();

  if (parenthPtr)
    *parenthPtr = '\0';

  for (i=ruleCount-1; i>=0; i--) {
    if (!strcmp (bindRules[i].name, name)) {
      if (parenthPtr)
	*parenthPtr = '(';
      return (TRUE);
    }
  }
  if (parenthPtr)
    *parenthPtr = '(';
  return (FALSE);
}
