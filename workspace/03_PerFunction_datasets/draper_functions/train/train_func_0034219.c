mark_bb_seen (basic_block bb)
{
  unsigned int size = SBITMAP_SIZE (bb_seen);

  if ((unsigned int)bb->index >= size)
    bb_seen = sbitmap_resize (bb_seen, size * 2, 0);

  bitmap_set_bit (bb_seen, bb->index);
}
