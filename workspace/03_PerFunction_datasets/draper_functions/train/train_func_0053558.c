df_chain_finalize (bitmap all_blocks)
{
  unsigned int bb_index;
  bitmap_iterator bi;

  EXECUTE_IF_SET_IN_BITMAP (all_blocks, 0, bb_index, bi)
    {
      df_chain_create_bb (bb_index);
    }
}
