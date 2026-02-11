cc2gc(struct cart *x)
{
  struct geo position;

  double tln;
  double tlt;
  double r;

  if ( !(fabs(x->x[0]) > 0.0) ) {
    if (x->x[1] >= 0.0) {
      position.lon = 0.5*M_PI;
    } else {
      position.lon = 1.5*M_PI;
    }
  } else {
    tln = x->x[1]/x->x[0];
    position.lon = atan(tln);
    if (x->x[0] < 0.0) {
      position.lon = position.lon + M_PI;
    }
    if (position.lon < 0.0) {
      position.lon = position.lon + 2*M_PI;
    }
  }

  r = sqrt(x->x[0]*x->x[0] + x->x[1]*x->x[1]);

  if ( !(fabs(r) > 0.0) ) {
    if (x->x[2] > 0.0) {
      position.lat =  0.5*M_PI;
    } else {
      position.lat = -0.5*M_PI;
    }
  } else {
    tlt = x->x[2]/r;
    position.lat = atan(tlt);
  }

  return (position);
}
