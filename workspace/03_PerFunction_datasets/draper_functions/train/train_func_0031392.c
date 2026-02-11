compute_mixed_vorticity (FttCell * cell, gpointer * data)
{
  GfsVariable * v = data[0];
  GfsVariable * u = data[1];
  FttVector g;

  g_assert (((cell)->flags & GFS_FLAG_DIRICHLET) != 0);
  gfs_cell_dirichlet_gradient (cell, u->i, -1, GFS_STATE (cell)->solid->fv, &g);
  if (u->component == FTT_X)
    GFS_VARIABLE (cell, v->i) -= g.y;
  else
    GFS_VARIABLE (cell, v->i) += g.x;
}
