mouse_attract_help (LLINT * x, LLINT * y)
{
  LLINT x_test, y_test;
  int i;
  int flag = 0;

  if (!attraction)
    return 0;

  for (i = 0; i < 2 * angle; i++)
    {
      x_test = x_begin + HELP_RADIUS * cos (angle_shift + (i * G_PI) / angle);
      y_test = y_begin + HELP_RADIUS * sin (angle_shift + (i * G_PI) / angle);
      if (SQR (*x - x_test) + SQR (*y - y_test) < HELP_CLOSE)
	{
	  flag = 1;
	  *x = x_test;
	  *y = y_test;
	}
    }

  return flag;
}
