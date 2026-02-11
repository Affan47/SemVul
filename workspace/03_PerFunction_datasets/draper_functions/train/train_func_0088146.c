GetAngle(float *pos_ptr, int A, int B, int C)
{
  Point2D a, b, c;
  float angle, dotprod, mag;
  double factor;

  a.x = pos_ptr[2*A];
  a.y = pos_ptr[2*A+1];

  b.x = pos_ptr[2*B];
  b.y = pos_ptr[2*B+1];

  c.x = pos_ptr[2*C];
  c.y = pos_ptr[2*C+1];

  dotprod = (a.x - b.x)*(c.x - b.x) + (a.y - b.y)*(c.y - b.y);
  mag = sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)) *
    sqrt((c.x-b.x)*(c.x-b.x) + (c.y-b.y)*(c.y-b.y));

  factor = dotprod/mag;
  if ((factor >= .99999)) {
     angle = 0.0;
  }
  else if ((factor <= -.99999)) {
     angle = 3.1415926;
  }
  else {
     angle = acos(factor);
  }
  return angle;
}
