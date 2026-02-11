GraphToWorld( double xg, double yg, double &xw, double &yw, bool reset ) const
{


  static double xlog, ylog, xlaxis, ylaxis, cosx, sinx, cosy, siny, ax, bx, ay, by, xmin, ymin;
  if( reset )GetValues( xlog, ylog, xlaxis, ylaxis, cosx, sinx, cosy, siny, ax, bx, ay, by, xmin, ymin );
  if( static_cast<int>(xlog) > 1 )
  {
    if( xg <= 0.0 )xg = std::numeric_limits<double>::min();
    xg = log(xg)/log(xlog);
  }
  if( static_cast<int>(ylog) > 1 )
  {
    if( yg <= 0.0 )yg = std::numeric_limits<double>::min();
    yg = log(yg)/log(ylog);
  }
  xw = xlaxis + cosx*(ax*xg+bx) + cosy*(ay*yg+by);
  yw = ylaxis + sinx*(ax*xg+bx) + siny*(ay*yg+by);
}
