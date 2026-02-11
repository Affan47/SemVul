clutter_vertex_init (ClutterVertex *vertex,
                     gfloat         x,
                     gfloat         y,
                     gfloat         z)
{
  g_return_val_if_fail (vertex != NULL, NULL);

  vertex->x = x;
  vertex->y = y;
  vertex->z = z;

  return vertex;
}
