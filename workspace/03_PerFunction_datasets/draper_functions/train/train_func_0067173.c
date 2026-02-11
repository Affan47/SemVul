in_window_primitive(const tenm_primitive *p)
{
  double temp_x;
  double temp_y;
  double temp_r;
  int i;

  if (window == NULL)
  {
    fprintf(stderr, "in_window_primitive: window is NULL\n");
    return 0;
  }
  if (p == NULL)
  {
    fprintf(stderr, "in_window_primitive: p is NULL\n");
    return 0;
  }

  switch (p->klass)
  {
  case TENM_POINT:
    return in_window_point(((const tenm_point *) p)->x,
                           ((const tenm_point *) p)->y);
    break;
  case TENM_CIRCLE:
    temp_x = ((const tenm_circle *) p)->center->x;
    temp_y = ((const tenm_circle *) p)->center->y;
    temp_r = ((const tenm_circle *) p)->r;
    if ((temp_x + temp_r >= 0.0) && (temp_x - temp_r < window_width)
        && (temp_y >= 0.0) && (temp_y < window_height))
      return 1;
    if ((temp_y + temp_r >= 0.0) && (temp_y - temp_r < window_height)
        && (temp_x >= 0.0) && (temp_x < window_width))
      return 1;
    return tenm_collided_primitive(p, window);
    break;
  case TENM_SEGMENT:
    temp_x = ((const tenm_segment *) p)->a->x;
    temp_y = ((const tenm_segment *) p)->a->y;
    if (in_window_point(temp_x, temp_y))
      return 1;
    temp_x = ((const tenm_segment *) p)->b->x;
    temp_y = ((const tenm_segment *) p)->b->y;
    if (in_window_point(temp_x, temp_y))
      return 1;
    return tenm_collided_primitive(p, window);
    break;
  case TENM_POLYGON:
    for (i = 0; i < ((const tenm_polygon *) p)->n; i++)
    {
      temp_x = ((const tenm_polygon *) p)->v[i]->x;
      temp_y = ((const tenm_polygon *) p)->v[i]->y;
      if (in_window_point(temp_x, temp_y))
        return 1;
    }
    return tenm_collided_primitive(p, window);
    break;
  default:
    fprintf(stderr, "primitive_in_window: strange primitive found (%d)\n",
            p->klass);
    return 0;
    break;
  }

  return 0;
}
