write_ts_optimization (struct output_block *ob, tree expr)
{
  struct cl_optimization *t = TREE_OPTIMIZATION (expr);
  struct bitpack_d bp;
  unsigned i, len;


  bp = bitpack_create (ob->main_stream);
  len = sizeof (struct cl_optimization);
  for (i = 0; i < len; i++)
    bp_pack_value (&bp, ((unsigned char *)t)[i], 8);

  bp_pack_value (&bp, 0x12345678, 32);
  streamer_write_bitpack (&bp);
}
