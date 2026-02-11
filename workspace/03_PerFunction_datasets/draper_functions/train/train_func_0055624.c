cube_new (CellCube * cube, FttCell * cell, GfsGenericSurface * s, FttVector * o, FttVector * h)
{
  guint i;

  for (i = 0; i < FTT_DIMENSION; i++)
    (&o->x)[i] -= (&h->x)[i]/2.;
  for (i = 0; i < 8; i++) {
    cube->p[i].x = o->x + h->x*vertex[i].x;
    cube->p[i].y = o->y + h->y*vertex[i].y;
    cube->p[i].z = o->z + h->z*vertex[i].z;
  }

  for (i = 0; i < 12; i++) {
    cube->s[i].E = &cube->p[edge1[i][0]];
    cube->s[i].D = &cube->p[edge1[i][1]];
    gfs_surface_segment_intersection (s, cell, &cube->s[i]);
  }
}
