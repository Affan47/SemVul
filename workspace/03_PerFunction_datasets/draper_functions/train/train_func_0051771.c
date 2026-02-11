tform_to_world (GGobiData * d, ggobid * gg)
{


  gint j;

  for (j = 0; j < d->ncols; j++)
    tform_to_world_by_var (j, d, gg);
}
