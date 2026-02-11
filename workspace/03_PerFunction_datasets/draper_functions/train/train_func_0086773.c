TriangleVolume( double x1, double x2, double x3,
                                             double y1, double y2, double y3,
                                             double z1, double z2, double z3 )
{


  double area = x2*y3-x3*y2 + x3*y1-x1*y3 + x1*y2-x2*y1;
  if( area < 0. )area = 0.;


  return (z1+z2+z3)*area/6.0;
}
