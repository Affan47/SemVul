restore_solid (FttCell * cell, gpointer * data)
{
  GfsVariable * status = data[0];
  GfsVariable * c = data[1];
  GfsSolidVector * solid = GFS_STATE (cell)->solid;

  GFS_STATE (cell)->solid = GFS_DOUBLE_TO_POINTER (GFS_VALUE (cell, c));
  if (solid) {
    GFS_VALUE (cell, c) = solid->a;
    g_free (solid);
  }
  else {
    g_assert (GFS_VALUE (cell, status) == GFS_STATUS_SOLID ||
	      GFS_VALUE (cell, status) == GFS_STATUS_FLUID);
    GFS_VALUE (cell, c) = GFS_VALUE (cell, status) - 1.;
  }
}
