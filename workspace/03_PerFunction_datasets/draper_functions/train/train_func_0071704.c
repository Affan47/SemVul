p_calc_angle(gint p1x, gint p1y, gint p2x, gint p2y)
{


  gdouble l_a;
  gdouble l_b;
  gdouble l_angle_rad;
  gdouble l_angle;

  l_a = p2x - p1x;
  l_b = (p2y - p1y) * (-1.0);

  if(l_a == 0)
  {
    if(l_b < 0)  { l_angle = 90.0; }
    else         { l_angle = 270.0; }
  }
  else
  {
    l_angle_rad = atan(l_b/l_a);
    l_angle = (l_angle_rad * 180.0) / G_PI;

    if(l_a < 0)
    {
      l_angle = 180 - l_angle;
    }
    else
    {
      l_angle = l_angle * (-1.0);
    }
  }

  if(gap_debug)
  {
     printf("p_calc_angle: p1(%d/%d) p2(%d/%d)  a=%f, b=%f, angle=%f\n"
         , (int)p1x, (int)p1y, (int)p2x, (int)p2y
         , (float)l_a, (float)l_b, (float)l_angle);
  }
  return(l_angle);
}
