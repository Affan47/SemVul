tohs(double x, double y, double& h, double& s) {
#ifdef CIRCLE
  x = 2*x-1;
  y = 1-2*y;
  s = sqrt(x*x+y*y); if (s > 1.0) s = 1.0;
  h = (3.0/M_PI)*atan2(y,x);
  if (h<0) h += 6.0;
#else
  h = fmod(6.0*x,6.0); if (h < 0.0) h += 6.0;
  s = 1.0-y; if (s < 0.0) s = 0.0; else if (s > 1.0) s = 1.0;
#endif
}
