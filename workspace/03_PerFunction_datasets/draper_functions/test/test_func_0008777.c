find_entry(const char *name)
{
  int a = 0;

  for (KCTDir::iterator it = _dir.begin();it != _dir.end();it++)
    {
      if (strcmp((*it)->name, name) == 0)
        return a;
      a++;
    }

  return -1;
}
