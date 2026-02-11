wall_4_move(tenm_object *my, double turn_per_frame)
{
  double dx_temp;
  double dy_temp;


  if (my == NULL)
  {
    fprintf(stderr, "wall_4_move: my is NULL\n");
    return 0;
  }
  if (turn_per_frame <= 0.5)
  {
    fprintf(stderr, "wall_4_move: strange turn_per_frame (%f)\n",
            turn_per_frame);
    return 0;
  }

  dx_temp = my->count_d[0] / turn_per_frame;
  dy_temp = my->count_d[1] / turn_per_frame;
  if ((my->count[1] > 0) && (my->count[0] < 0))
    dx_temp = 0.0;
  my->x += dx_temp;
  my->y += dy_temp;
  if (my->mass != NULL)
    tenm_move_mass(my->mass, dx_temp, dy_temp);

  if (my->y > ((double) WINDOW_HEIGHT) + 31.0)
    return 1;

  return 0;
}
