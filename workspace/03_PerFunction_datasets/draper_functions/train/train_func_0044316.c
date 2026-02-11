free_strinfo (strinfo si)
{
  if (si && --si->refcount == 0)
    pool_free (strinfo_pool, si);
}
