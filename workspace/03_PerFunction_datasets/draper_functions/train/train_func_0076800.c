gfs_cell_advected_face_values (FttCell * cell,
				    const GfsAdvectionParams * par)
{
  g_return_if_fail (cell != NULL);
  g_return_if_fail (par != NULL);

  GfsStateVector * s = GFS_STATE (cell);
  gdouble size = ftt_cell_size (cell), msize[FTT_DIMENSION];

  FttComponent c;
  if (par->v->domain->scale_metric)
    for (c = 0; c < FTT_DIMENSION; c++)
      msize[c] = size*(* par->v->domain->scale_metric) (par->v->domain, cell, c);
  else
    for (c = 0; c < FTT_DIMENSION; c++)
      msize[c] = size;

  for (c = 0; c < FTT_DIMENSION; c++) {
    gdouble unorm = par->use_centered_velocity ?
      par->dt*GFS_VALUE (cell, par->u[c])/msize[c] :
       par->dt*(s->f[2*c].un + s->f[2*c + 1].un)/(2.*msize[c]);
    gdouble g = (* par->gradient) (cell, c, par->v->i);
    gdouble vl = GFS_VALUE (cell, par->v) + MIN ((1. - unorm)/2., 0.5)*g;
    gdouble vr = GFS_VALUE (cell, par->v) + MAX ((- 1. - unorm)/2., -0.5)*g;
    gdouble src = par->dt*gfs_variable_mac_source (par->v, cell)/2.;
    gdouble dv;

#if FTT_2D
    dv = transverse_term (cell, msize, FTT_ORTHOGONAL_COMPONENT (c), par);
#else
    static FttComponent orthogonal[FTT_DIMENSION][2] = {
      {FTT_Y, FTT_Z}, {FTT_X, FTT_Z}, {FTT_X, FTT_Y}
    };

    dv =  transverse_term (cell, msize, orthogonal[c][0], par);
    dv += transverse_term (cell, msize, orthogonal[c][1], par);
#endif

    s->f[2*c].v     = vl + src - dv;
    s->f[2*c + 1].v = vr + src - dv;
  }
}
