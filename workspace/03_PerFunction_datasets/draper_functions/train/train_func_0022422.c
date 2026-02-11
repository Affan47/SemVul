write_ts_vector_tree_pointers (struct output_block *ob, tree expr, bool ref_p)
{
  unsigned i;


  for (i = 0; i < VECTOR_CST_NELTS (expr); ++i)
    stream_write_tree (ob, VECTOR_CST_ELT (expr, i), ref_p);
}
