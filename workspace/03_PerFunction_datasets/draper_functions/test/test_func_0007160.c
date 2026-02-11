gegl_expcombine_normalize (gfloat *response,
                           guint   steps)
{
  guint  step_min, step_max, step_mid;
  guint  i;
  gfloat val_mid;

  g_return_val_if_fail (response, NAN);
  g_return_val_if_fail (steps > 0, NAN);


  for (step_min = 0;
       step_min < steps && response[step_min] == 0;
       ++step_min)
    ;
  for (step_max = steps - 1;
       step_max > 0 && response[step_max] == 0;
       --step_max)
    ;

  g_return_val_if_fail (step_max >= step_min, NAN);
  step_mid = step_min + (step_max - step_min) / 2;


  val_mid = response[step_mid];
  if (val_mid == 0.0f)
  {

    while (step_mid < step_max && response[step_mid] == 0.0f)
        ++step_mid;
    val_mid = response[step_mid];
  }


  g_return_val_if_fail (val_mid != 0.0f, 0.0f);

  for (i = 0; i < steps; ++i)
      response[i] /= val_mid;

  return val_mid;
}
