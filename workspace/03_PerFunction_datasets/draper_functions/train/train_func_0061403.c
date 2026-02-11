silver_chimera_spread_move(tenm_object *my, double turn_per_frame)
{
  double dx_temp;
  double dy_temp;


  if (my == NULL)
  {
    fprintf(stderr, "silver_chimera_spread_move: my is NULL\n");
    return 0;
  }
  if (turn_per_frame <= 0.5)
  {
    fprintf(stderr, "silver_chimera_spread_move: "
            "strange turn_per_frame (%f)\n",
            turn_per_frame);
    return 0;
  }

  dx_temp = my->count_d[0] / turn_per_frame;
  dy_temp = my->count_d[1] / turn_per_frame;
  my->x += dx_temp;
  my->y += dy_temp;
  if (my->mass != NULL)
    tenm_move_mass(my->mass, dx_temp, dy_temp);


  if ((my->count[1] == 1) && (my->mass != NULL))
    ((tenm_circle *)(my->mass->p[0]))->r += 2.0 / turn_per_frame;

  if (!in_window_object(my))
    return 1;

  return 0;
}
