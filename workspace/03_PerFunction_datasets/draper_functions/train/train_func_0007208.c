citymap_is_reserved(struct tile *ptile)
{
  if (NULL != tile_worked(ptile) ) {
    return TRUE;
  }
  return (citymap[tile_index(ptile)] < 0);
}
