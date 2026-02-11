isOrthogonal (const Hep3Vector & v,
			     double epsilon) const {


  static const double TOOBIG = std::pow(2.0,507);
  static const double SCALE = std::pow(2.0,-507);
  double v1v2 = std::fabs(dot(v));

  if ( v1v2 >= TOOBIG ) {
    Hep3Vector sv1 ( *this * SCALE );
    Hep3Vector sv2 ( v * SCALE );
    Hep3Vector sv1Xsv2 = sv1.cross(sv2);
    double x2 = sv1Xsv2.mag2();
    double limit = epsilon*epsilon*x2;
    double y2 = v1v2*SCALE*SCALE;
    return ( y2*y2 <= limit );
  }


  Hep3Vector eps_v1Xv2 ( cross(epsilon*v) );
  if (  (std::fabs (eps_v1Xv2.dx) > TOOBIG) ||
        (std::fabs (eps_v1Xv2.dy) > TOOBIG) ||
        (std::fabs (eps_v1Xv2.dz) > TOOBIG) ) {
    return true;
  }


  return ( v1v2*v1v2 <= eps_v1Xv2.mag2() );

}
