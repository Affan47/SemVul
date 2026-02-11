nearest_common_dominator_for_set (enum cdi_direction dir, bitmap blocks)
{
  unsigned i, first;
  bitmap_iterator bi;
  basic_block dom;

  first = bitmap_first_set_bit (blocks);
  dom = BASIC_BLOCK (first);
  EXECUTE_IF_SET_IN_BITMAP (blocks, 0, i, bi)
    if (dom != BASIC_BLOCK (i))
      dom = nearest_common_dominator (dir, dom, BASIC_BLOCK (i));

  return dom;
}
