box_destroy (GfsBox * box, GfsVariable * newboxp)
{
  GfsBox * newbox[FTT_CELLS];
  FttCellChildren child;
  guint i;

  ftt_cell_children (box->root, &child);
  for (i = 0; i < FTT_CELLS; i++)
    if (child.c[i])
      newbox[i] = GFS_DOUBLE_TO_POINTER (GFS_VALUE (child.c[i], newboxp));
    else
      newbox[i] = NULL;

  ftt_cell_destroy_root (box->root, &child, (FttCellCleanupFunc) gfs_cell_cleanup,
			 gfs_box_domain (box));
  box->root = NULL;
  for (i = 0; i < FTT_CELLS; i++)
    if (child.c[i]) {
      newbox[i]->root = child.c[i];
      FTT_ROOT_CELL (newbox[i]->root)->parent = newbox[i];
    }

  gts_object_destroy (GTS_OBJECT (box));
}
