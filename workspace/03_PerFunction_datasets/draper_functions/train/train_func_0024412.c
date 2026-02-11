explosion_draw(tenm_object *my, int priority)
{
  int i;
  int suffix;
  int status = 0;
  tenm_color color;
  int temp;


  if (my == NULL)
    return 0;
  if (priority != 0)
    return 0;
  if (my->count[0] <= 0)
    return 0;

  switch (my->count[2])
  {


  case 0:
    color = tenm_map_color(99, 158, 79);
    color = tenm_map_color(99, 158, 114);
    break;

  case 1:
    color = tenm_map_color(99, 158, 114);
    color = tenm_map_color(99, 158, 138);
    break;

  case 2:
    color = tenm_map_color(79, 138, 158);
    color = tenm_map_color(99, 143, 158);
    break;

  case 3:
    color = tenm_map_color(79, 118, 158);
    color = tenm_map_color(99, 128, 158);
    break;

  case 4:
    color = tenm_map_color(118, 99, 158);
    break;

  case 5:
    color = tenm_map_color(142, 99, 158);
    break;


  case 6:
    color = tenm_map_color(158, 158, 158);
    break;


  case 7:
    color = tenm_map_color(95, 47, 13);
    break;

  case 8:
    color = tenm_map_color(61, 95, 13);
    break;

  case 9:
    color = tenm_map_color(95, 13, 68);
    break;

  case 10:
    color = tenm_map_color(10, 75, 139);
    break;
  default:
    color = tenm_map_color(0, 0, 0);
    break;
  }

  temp = my->count[0] / 2;
  for (i = 0; i < my->count[1]; i++)
  {
    suffix = i * 4 + 4;
    if (tenm_draw_rectangle(((int) (my->count_d[0] + my->count_d[suffix + 0]))
                            - temp,
                            ((int) (my->count_d[1] + my->count_d[suffix + 1]))
                            - temp,
                            my->count[0], my->count[0],
                            color) != 0)
      status = 1;
  }
  return status;
}
