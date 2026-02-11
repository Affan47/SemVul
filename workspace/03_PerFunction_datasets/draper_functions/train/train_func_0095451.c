compute_w (FttCell * c, GfsVariable * W)
{
  FttCell * n;
  guint level = ftt_cell_level (c);
  gdouble wf = 0., w = 0.;

  while ((n = ftt_cell_neighbor (c, FTT_BACK)))
    c = n;
  while (c) {
    GfsStateVector * s = GFS_STATE (c);

    g_assert (FTT_CELL_IS_LEAF (c) && ftt_cell_level (c) == level);
    s->f[FTT_BACK].un = w;
    wf += (s->f[FTT_LEFT].v*s->f[FTT_LEFT].un - s->f[FTT_RIGHT].v*s->f[FTT_RIGHT].un +
    	   s->f[FTT_BOTTOM].v*s->f[FTT_BOTTOM].un - s->f[FTT_TOP].v*s->f[FTT_TOP].un);
    if (GFS_IS_MIXED (c))
      s->f[FTT_FRONT].un = w = GFS_STATE (c)->solid->s[FTT_FRONT] > 0. ?
	wf/GFS_STATE (c)->solid->s[FTT_FRONT] : 0.;
    else
      s->f[FTT_FRONT].un = w = wf;
    GFS_VARIABLE (c, W->i) = (s->f[FTT_BACK].un + s->f[FTT_FRONT].un)/2.;
    c = ftt_cell_neighbor (c, FTT_FRONT);
  }
}
