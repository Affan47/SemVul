last_boss_star_dust_draw(tenm_object *my, int priority)
{
  tenm_color color;
  int status = 0;


  if (my == NULL)
    return 0;

  if (priority != 0)
    return 0;

  color = tenm_map_color(118, 99, 158);
  if (my->count[1] > 0)
    if (tenm_draw_circle((int) (my->x), (int) (my->y),
                         my->count[1], 1, color) != 0)
      status = 1;

  color = tenm_map_color(158, 158, 158);
  if (my->count[1] > 50)
    if (tenm_draw_circle((int) (my->x), (int) (my->y),
                         (my->count[1] - 50) * 2, 1, color) != 0)
      status = 1;

  return status;
}
