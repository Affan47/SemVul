make_preds_opaque (basic_block b, int j)
{
  edge e;
  edge_iterator ei;

  FOR_EACH_EDGE (e, ei, b->preds)
    {
      basic_block pb = e->src;

      if (e->aux || ! bitmap_bit_p (transp[pb->index], j))
	continue;

      bitmap_clear_bit (transp[pb->index], j);
      make_preds_opaque (pb, j);
    }
}
