vocabulary_lookup_sname(char **snames_list, char *sname)
{
  int pos = 0;
  while (snames_list[pos])
  {
	  if (!strcasecmp(sname, snames_list[pos])) return pos;
	  pos++;
  }

  return -1;
}
