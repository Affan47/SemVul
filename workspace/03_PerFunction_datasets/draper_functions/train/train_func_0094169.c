src_to_dest_compare (void const *x, void const *y)
{
  struct Src_to_dest const *a = x;
  struct Src_to_dest const *b = y;
  return SAME_INODE (*a, *b) ? true : false;
}
