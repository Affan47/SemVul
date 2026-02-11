gamgi_mesa_rotate_direction_list (double angle, double *axis)
{
gamgi_layer *layer = NULL;
gamgi_direction *direction;
gamgi_dlist *dlist;
double rotate[9];
double quaternion[4];

for (dlist = gamgi->directions; dlist != NULL; dlist = dlist->next)
  {
  direction = GAMGI_CAST_DIRECTION dlist->data;
  if (direction->model != GAMGI_PHYS_LINE) continue;

  static_layer (GAMGI_CAST_OBJECT direction,
  &layer, angle, axis, quaternion, rotate);
  gamgi_mesa_rotate_direction (direction, quaternion, rotate, direction->center);
  }
}
