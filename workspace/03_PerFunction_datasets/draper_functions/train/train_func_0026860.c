map_startpos_get(const struct tile *ptile)
{
  struct startpos *psp;

  fc_assert_ret_val(NULL != ptile, NULL);
  fc_assert_ret_val(NULL != map.startpos_table, NULL);

  startpos_hash_lookup(map.startpos_table, tile_hash_key(ptile), &psp);
  return psp;
}
