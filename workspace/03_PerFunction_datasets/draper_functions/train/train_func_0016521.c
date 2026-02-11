mapdeco_is_highlight_set(const struct tile *ptile)
{
  if (!ptile || !mapdeco_highlight_table) {
    return FALSE;
  }
  return tile_hash_lookup(mapdeco_highlight_table, ptile, NULL);
}
