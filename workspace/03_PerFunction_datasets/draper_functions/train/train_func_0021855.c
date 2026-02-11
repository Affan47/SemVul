eventone_update(stpi_dither_channel_t *dc, eventone_t *et,
		int x, int direction)
{
  shade_distance_t *sp = (shade_distance_t *) dc->aux_data;
  distance_t *etd = &sp->et_dis[x];
  int t = etd->r_sq + etd->dy;
  int u = sp->dis.r_sq + sp->dis.dy;
  if (u < t)
    {
      t = u;
      etd->dx = sp->dis.dx;
      etd->dy = sp->dis.dy;
    }
  etd->dy += et->d2y;

  if (t > 65535)
    t = 65535;
  etd->r_sq = t;
}
