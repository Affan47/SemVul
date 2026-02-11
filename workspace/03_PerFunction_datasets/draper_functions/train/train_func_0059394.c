skewX (float angle)
{
  double mod_angle = static_cast<double>(angle);

  if (mod_angle > 180.0)
    mod_angle -= floor (mod_angle / 180.0) * 180.0;
  else if (mod_angle < 0.0)
    mod_angle += (1.0 + floor ((-mod_angle) / 180.0)) * 180.0;

  if ((mod_angle > 89.9) && (mod_angle < 90.1))
    {
      UT_SVGMatrix neo(a, b, c, d, e, f);
      return neo;
    }

  float T = static_cast<float>(tan ((mod_angle * UT_PI) / 180.0));

  UT_SVGMatrix neo(a, b, a*T+c, b*T+d, e, f);

  return neo;
}
