draw_cfg_nodes_no_loops (pretty_printer *pp, struct function *fun)
{
  int *rpo = XNEWVEC (int, n_basic_blocks_for_function (fun));
  int i, n;
  sbitmap visited;

  visited = sbitmap_alloc (last_basic_block);
  bitmap_clear (visited);


  n = pre_and_rev_post_order_compute (NULL, rpo, true);
  for (i = 0; i < n; i++)
    {
      basic_block bb = BASIC_BLOCK (rpo[i]);
      draw_cfg_node (pp, fun->funcdef_no, bb);
      bitmap_set_bit (visited, bb->index);
    }
  free (rpo);

  if (n != n_basic_blocks_for_function (fun))
    {

      basic_block bb;
      FOR_ALL_BB_FN (bb, fun)
	if (! bitmap_bit_p (visited, bb->index))
	  draw_cfg_node (pp, fun->funcdef_no, bb);
    }

  sbitmap_free (visited);
}
