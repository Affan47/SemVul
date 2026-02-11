scale_angle(double gamma, double )
{
  const double r_factor = 0.3;
  const double theta_factor = 0.6;

  xy_to_rtheta();


  if (theta() > TWO_VERDICT_PI - 0.02)
    theta() = 0;


  if ( gamma < 1 )
  {


    theta() += (VERDICT_PI-theta())*(1-gamma)*theta_factor*(1-r());


    r( (r_factor + r()) / (1 + r_factor) );


    theta() *= gamma;
  }
  else
  {

    double new_theta = theta() * gamma;
    if ( new_theta < 2.5 * VERDICT_PI || r() < 0.2)
      theta( new_theta );
  }
  rtheta_to_xy();
}
