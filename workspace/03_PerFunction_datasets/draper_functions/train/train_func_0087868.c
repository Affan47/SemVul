map_startpos_remove(struct tile *ptile)
{
  fc_assert_ret_val(NULL != ptile, FALSE);
  fc_assert_ret_val(NULL != map.startpos_table, FALSE);

  return startpos_hash_remove(map.startpos_table, tile_hash_key(ptile));
}
