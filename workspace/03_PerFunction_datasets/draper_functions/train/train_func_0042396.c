watcher_below_bit_draw(tenm_object *my, int priority)
{
  int status = 0;
  tenm_color color;
  char temp[32];
  int width;


  if (my == NULL)
  {
    fprintf(stderr, "watcher_below_bit_draw: my is NULL\n");
    return 0;
  }


  if ((priority == 0) && (my->count[2] <= 1))
  {
    if (watcher_below_bit_green(my))
    {
      if (my->count[1] >= 40)
        color = tenm_map_color(181, 190, 92);
      else
        color = tenm_map_color(157, 182, 123);
    }
    else
    {
      if (my->count[1] >= 40)
        color = tenm_map_color(200, 164, 92);
      else
        color = tenm_map_color(182, 147, 123);
    }
  }


  if (priority == 0)
  {
    if (watcher_below_bit_green(my))
    {
      if (my->count[1] >= 1)
        color = tenm_map_color(109, 125, 9);
      else
        color = tenm_map_color(61, 95, 13);
    }
    else
    {
      if (my->count[1] >= 1)
        color = tenm_map_color(135, 89, 9);
      else
        color = tenm_map_color(95, 47, 13);
    }

    if (my->attr != 0)
      width = 3;
    else
      width = 1;

    if (tenm_draw_circle((int) (my->x), (int) (my->y), 25, width, color) != 0)
      status = 1;
  }


  if ((priority == 0) && (my->count[1] >= 1))
  {
    sprintf(temp, "%d", my->hit_point);
    if (draw_string(((int) my->x) - 10, (int) my->y,
                    temp, (int) strlen(temp)) != 0)
    {
      fprintf(stderr, "watcher_below_bit_draw: draw_string failed\n");
      status = 1;
    }
  }

  return status;
}
