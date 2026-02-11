refine_leaf_boxes (GfsBox * box, GfsDomain * domain)
{


  if (FTT_CELL_IS_LEAF (box->root)) {
    ftt_cell_refine_single (box->root, domain->cell_init, domain->cell_init_data);
    gfs_cell_coarse_init (box->root, domain);
    ftt_cell_coarsen (box->root,
		      (FttCellCoarsenFunc) coarsen_cell, NULL,
		      (FttCellCleanupFunc) gfs_cell_cleanup, domain);
  }
}
