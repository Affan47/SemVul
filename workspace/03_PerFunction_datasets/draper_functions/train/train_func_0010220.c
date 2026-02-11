ab_to_chab (double  a,
            double  b,
            double *C,
            double *H)
{
  *C = sqrt (a * a + b * b);
  *H = atan2 (b, a) * DEGREES_PER_RADIAN;


  if (*H < 0.0)
    *H += 360;
}
