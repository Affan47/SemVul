rtl_create_basic_block (void *headp, void *endp, basic_block after)
{
  rtx head = (rtx) headp, end = (rtx) endp;
  basic_block bb;


  if ((size_t) last_basic_block >= VEC_length (basic_block, basic_block_info))
    {
      size_t new_size = last_basic_block + (last_basic_block + 3) / 4;
      VEC_safe_grow_cleared (basic_block, gc, basic_block_info, new_size);
    }

  n_basic_blocks++;

  bb = create_basic_block_structure (head, end, NULL, after);
  bb->aux = NULL;
  return bb;
}
