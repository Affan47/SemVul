nssHash_Destroy
(
  nssHash *hash
)
{
  (void)PZ_DestroyLock(hash->mutex);
  PL_HashTableDestroy(hash->plHashTable);
  if (hash->i_alloced_arena) {
    nssArena_Destroy(hash->arena);
  } else {
    nss_ZFreeIf(hash);
  }
}
