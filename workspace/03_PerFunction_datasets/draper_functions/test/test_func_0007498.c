center_periodic_rotate (FttCellFace * face, GfsBc * b)
{
  GfsBoundaryPeriodic * boundary_periodic = GFS_BOUNDARY_PERIODIC (b->b);

  g_assert (boundary_periodic->sndcount < boundary_periodic->sndbuf->len);
  g_assert (ftt_face_type (face) == FTT_FINE_FINE);
  g_assert (!FTT_CELL_IS_LEAF (face->cell) || FTT_CELL_IS_LEAF (face->neighbor));

  if (b->v->component < 2) {
    FttComponent c = FTT_ORTHOGONAL_COMPONENT (b->v->component);
    g_assert (b->v->vector[c]);
    g_array_index (boundary_periodic->sndbuf, gdouble, boundary_periodic->sndcount++) =
      (2.*c - 1.)*boundary_periodic->rotate*GFS_VALUE (face->neighbor, b->v->vector[c]);
  }
  else
    g_array_index (boundary_periodic->sndbuf, gdouble, boundary_periodic->sndcount++) =
      GFS_VALUE (face->neighbor, b->v);
}
