theorem_weapon_shot_absolute_new(double x, double y,
                                 double player_x, double player_y,
                                 double speed, int theta, int what, int color)
{

  if (speed < NEAR_ZERO)
  {
    fprintf(stderr, "theorem_weapon_shot_absolute_new: speed is non-positive "
            "(%f)\n", speed);
    return NULL;
  }
  if ((color != 0) && (color != 1))
  {
    fprintf(stderr, "theorem_weapon_shot_absolute_new: wrong color "
            "(%d)\n", color);
    return NULL;
  }

  return theorem_weapon_shot_new(x, y, player_x, player_y,
                                 speed * tenm_cos(theta),
                                 speed * tenm_sin(theta),
                                 what, color);
}
