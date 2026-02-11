_real_is_a(const char* repoId)
{
  if( !repoId )  return 0;

  if( _ptrToObjRef(repoId) )                             return 1;
  if( omni::ptrStrMatch(repoId, pd_mostDerivedRepoId) )  return 1;


  return _remote_is_a(repoId);
}
