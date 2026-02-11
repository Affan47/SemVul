already_processed_vertex_p (bitmap processed, int v)
{
  return (bitmap_bit_p (processed, v)
	  || !bitmap_bit_p (remaining_stmts, v));
}
