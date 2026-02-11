pie_intercept(int width, int height, double xcen, double ycen,
			 double angle, double *xcept, double *ycept)
{
  double angl, slope;
  angl = angle;

  while (angl < 0.0)
    angl = angl + 360.0;
  while (angl >= 360.0)
    angl = angl - 360.0;

#if USE_ASTRO_ANGLE
  if(fabs(angl - 90.0) < SMALL_NUMBER) {
#else
  if(fabs(angl - 180.0) < SMALL_NUMBER) {
#endif
    *xcept = 0.0;
    *ycept = ycen;
    return(2);
  }
#if USE_ASTRO_ANGLE
  if(fabs(angl - 270.0) < SMALL_NUMBER) {
#else
  if(fabs(angl - 0.0) < SMALL_NUMBER) {
#endif
    *xcept = width + 1;
    *ycept = ycen;
    return(4);
  }
#if USE_ASTRO_ANGLE

  angl = angl + 90.0;
#else
  angl = angl;
#endif
  if(angl >= 360.0)
    angl = angl - 360.0;
  if(angl < 180.0) {
    *ycept = height + 1;

    if(fabs(angl - 90.0) < SMALL_NUMBER) {
      *xcept = xcen;
      return(1);
    }
  } else {
    *ycept = 0.0;

    if(fabs(angl - 270.0) < SMALL_NUMBER) {
      *xcept = xcen;
      return(3);
    }
  }

  angl = (angl / 180.0) * M_PI;

  slope = tan(angl);

  *xcept = xcen + ((*ycept - ycen) / slope);
  if(*xcept < 0) {
    *ycept = (ycen - (xcen * slope));
    *xcept = 0.0;
    return(2);
  } else if(*xcept > (width + 1)) {
    *ycept = (ycen + ((width + 1 - xcen) * slope));
    *xcept = width + 1;
    return(4);
  } else {
    if(*ycept < height)
      return(3);
    else
      return(1);
  }
}
