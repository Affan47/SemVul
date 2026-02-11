FindNameOnList(char *name, char **list, int listLen)
{
  int found = -1;

  for (int i=0; i<listLen; i++)
    {
    if (!strcmp(name, list[i]))
      {
      found = i;
      break;
      }
    }

  return found;
}
