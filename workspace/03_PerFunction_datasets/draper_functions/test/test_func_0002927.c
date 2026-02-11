find(const char *name)
{
  ArSyncTask *proc;
  std::multimap<int, ArSyncTask *>::iterator it;

  if (strcmp(myName.c_str(), name) == 0)
    return this;

  for (it = myMultiMap.begin(); it != myMultiMap.end(); ++it)
  {
    proc = (*it).second;
    if (proc->find(name) != NULL)
      return proc;
  }
  return NULL;

}
