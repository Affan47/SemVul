nssCKFWHash_Exists
(
  nssCKFWHash *hash,
  const void *it
)
{
  void *value;

  if( CKR_OK != nssCKFWMutex_Lock(hash->mutex) ) {
    return CK_FALSE;
  }

  value = PL_HashTableLookup(hash->plHashTable, it);

  (void)nssCKFWMutex_Unlock(hash->mutex);

  if (!value) {
    return CK_FALSE;
  } else {
    return CK_TRUE;
  }
}
