HTMLGetTag(p)
MLElement p;
{
  int i;
  char *name;

  if ((name = MLTagName(p)) == NULL) return(NULL);

  for (i = 0; i < tlist_len; i++)
  {
    if (tlist[i].name != NULL &&
	strlen(name) == strlen(tlist[i].name) &&
	strcasecmp(name, tlist[i].name) == 0 &&
	!HTMLTestM(&tlist[i], MARKUP_FAKE))
    {
      return(&tlist[i]);
    }
  }

  return(NULL);
}
