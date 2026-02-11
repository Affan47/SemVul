seiron_fake_explosion(tenm_object *my)
{
  int n;
  double speed_theta;


  if (my == NULL)
    return;
  if ((my->count[2] >= 1992) && (my->count[2] < 3744))
  {
    n = 8;
    speed_theta = 30.0;
  }
  else
  {
    n = 7;
    speed_theta = -15.0;
  }
  tenm_table_add(fragment_new(my->x, my->y - 30.0, 0.0, -2.0,
                              50.0, 36, n, 4.0, speed_theta, 20));
  tenm_table_add(fragment_new(my->x, my->y + 30.0, 0.0, 2.0,
                              50.0, 36, n, 4.0, -speed_theta, 20));
  tenm_table_add(explosion_new(my->x, my->y, 0.0, 0.0,
                               1, 3000, n, 5.0, 8));


  tenm_mass_delete(my->mass);
  my->mass = NULL;
  tenm_table_apply_all((int (*)(tenm_object *, int)) (&delete_enemy_shot), 0);
  tenm_table_apply_all((int (*)(tenm_object *, int)) (&delete_enemy), 0);
  my->count[0] = 0;
  my->count[1] = 0;
  my->count[11] = 2;
  my->count[12] = 0;


  return;
}
