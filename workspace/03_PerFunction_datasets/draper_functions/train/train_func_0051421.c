release_key_hash_table (KeyHashTable tbl)
{
  int i;

  if (!tbl)
    return;
  for (i=0; i < 1024; i++)
    release_key_items (tbl[i]);
  xfree (tbl);
}
