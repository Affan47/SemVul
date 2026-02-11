_ptrToValue(const char* repoId)
{
  if (repoId == _PD_repoId)
    return (void*)this;
  if (omni::strMatch(repoId, _PD_repoId))
    return (void*)this;
  return 0;
}
