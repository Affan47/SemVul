prune_nrv_in_block (bitmap nrv, tree block)
{
  bool has_nrv = false;
  tree t;


  for (t = BLOCK_SUBBLOCKS (block); t; t = BLOCK_CHAIN (t))
    has_nrv |= prune_nrv_in_block (nrv, t);


  for (t = BLOCK_VARS (block); t; t = DECL_CHAIN (t))
    if (is_nrv_p (nrv, t))
      {
	if (has_nrv)
	  bitmap_clear_bit (nrv, DECL_UID (t));
	else
	  has_nrv = true;
      }

  return has_nrv;
}
