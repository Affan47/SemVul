add_scope_conflicts (void)
{
  basic_block bb;
  bool changed;
  bitmap work = BITMAP_ALLOC (NULL);
  int *rpo;
  int n_bbs;


  FOR_ALL_BB (bb)
    bb->aux = BITMAP_ALLOC (&stack_var_bitmap_obstack);

  rpo = XNEWVEC (int, last_basic_block);
  n_bbs = pre_and_rev_post_order_compute (NULL, rpo, false);

  changed = true;
  while (changed)
    {
      int i;
      changed = false;
      for (i = 0; i < n_bbs; i++)
	{
	  bitmap active;
	  bb = BASIC_BLOCK (rpo[i]);
	  active = (bitmap)bb->aux;
	  add_scope_conflicts_1 (bb, work, false);
	  if (bitmap_ior_into (active, work))
	    changed = true;
	}
    }

  FOR_EACH_BB (bb)
    add_scope_conflicts_1 (bb, work, true);

  free (rpo);
  BITMAP_FREE (work);
  FOR_ALL_BB (bb)
    BITMAP_FREE (bb->aux);
}
