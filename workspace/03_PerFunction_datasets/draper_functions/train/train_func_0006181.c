surf3d_rotate (surf3d * s, float angle)
{
  int i;
  float cosa;
  float sina;

  SINCOS (angle, sina, cosa);
  for (i = 0; i < s->nbvertex; i++) {
    Y_ROTATE_V3D (s->vertex[i], s->svertex[i], cosa, sina);
  }
}
