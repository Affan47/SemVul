wall_0_draw(tenm_object *my, int priority)
{
  int status = 0;
  tenm_color color;


  if (my == NULL)
  {
    fprintf(stderr, "wall_0_draw: my is NULL\n");
    return 0;
  }

  if (priority != 0)
    return 0;


  color = tenm_map_color(95, 13, 68);

  if (tenm_draw_line(((int) (my->x - 30.0)),
                     ((int) (my->y - 30.0)),
                     ((int) (my->x + 30.0)),
                     ((int) (my->y + 30.0)),
                     1, color) != 0)
    status = 1;
  if (tenm_draw_line(((int) (my->x + 30.0)),
                     ((int) (my->y - 30.0)),
                     ((int) (my->x - 30.0)),
                     ((int) (my->y + 30.0)),
                     1, color) != 0)
    status = 1;

  if (tenm_draw_line(((int) (my->x + 30.0)),
                     ((int) (my->y - 30.0)),
                     ((int) (my->x + 30.0)),
                     ((int) (my->y + 30.0)),
                     2, color) != 0)
    status = 1;
  if (tenm_draw_line(((int) (my->x + 30.0)),
                     ((int) (my->y + 30.0)),
                     ((int) (my->x - 30.0)),
                     ((int) (my->y + 30.0)),
                     2, color) != 0)
    status = 1;
  if (tenm_draw_line(((int) (my->x - 30.0)),
                     ((int) (my->y + 30.0)),
                     ((int) (my->x - 30.0)),
                     ((int) (my->y - 30.0)),
                     2, color) != 0)
    status = 1;
  if (tenm_draw_line(((int) (my->x - 30.0)),
                     ((int) (my->y - 30.0)),
                     ((int) (my->x + 30.0)),
                     ((int) (my->y - 30.0)),
                     2, color) != 0)
    status = 1;

  return status;
}
