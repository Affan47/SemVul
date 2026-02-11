nget(struct names *names, const char *name)
{
  while (names)
    {
      if (strcmp(name,names->name) == 0)
	return names->value;
      else
	names = names->next;
    }


  return 0;
}
