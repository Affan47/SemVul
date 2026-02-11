isParallel (const Hep3Vector & v,
                              double epsilon) const {


  static const double TOOBIG = std::pow(2.0,507);
  static const double SCALE  = std::pow(2.0,-507);
  double v1v2 = std::fabs(dot(v));
  if ( v1v2 == 0 ) {
    return ( (mag2() == 0) && (v.mag2() == 0) );
  }
  if ( v1v2 >= TOOBIG ) {
    Hep3Vector sv1 ( *this * SCALE );
    Hep3Vector sv2 ( v * SCALE );
    Hep3Vector sv1Xsv2 = sv1.cross(sv2);
    double x2 = sv1Xsv2.mag2();
    double limit = v1v2*SCALE*SCALE;
    limit = epsilon*epsilon*limit*limit;
    return ( x2 <= limit );
  }


  Hep3Vector v1Xv2 ( cross(v) );
  if (  (std::fabs (v1Xv2.dx) > TOOBIG) ||
        (std::fabs (v1Xv2.dy) > TOOBIG) ||
        (std::fabs (v1Xv2.dz) > TOOBIG) ) {
    return false;
  }

  return ( (v1Xv2.mag2()) <= ((epsilon * v1v2) * (epsilon * v1v2)) );

}
