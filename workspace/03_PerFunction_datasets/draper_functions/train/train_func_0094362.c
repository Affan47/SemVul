tenm_sin(int theta)
{
  if (sin_table == NULL)
    return sin(2.0 * pi * ((double) theta) / 360.0);

  while (theta < 0)
    theta += 360;
  while (theta >= 360)
    theta -= 360;
  return sin_table[theta];
}
