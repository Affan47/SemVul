bitmap_lock_clear_bit(MY_BITMAP *map, uint bitmap_bit)
{
  bitmap_lock(map);
  DBUG_ASSERT(map->bitmap && bitmap_bit < map->n_bits);
  bitmap_clear_bit(map, bitmap_bit);
  bitmap_unlock(map);
}
