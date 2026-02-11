InverseCDF(double p)
{
  double dp, dx, dt, ddq, dq;
  int    newt;

  dp = ( p <= 0.5 ) ? ( p ) : ( 1.0 - p );


  if ( p <= 0.0 )
    {
    return itk::NumericTraits< double >::NonpositiveMin();
    }
  else if ( p >= 1.0 )
    {
    return itk::NumericTraits< double >::max();
    }


  dt = std::sqrt( -2.0 * std::log(dp) );
  dx = dt
       - ( ( .010328e+0 * dt + .802853e+0 ) * dt + 2.515517e+0 )
       / ( ( ( .001308e+0 * dt + .189269e+0 ) * dt + 1.432788e+0 ) * dt + 1.e+0 );


  for ( newt = 0; newt < 3; newt++ )
    {
    dq  = 0.5e+0 * vnl_erfc(dx * itk::Math::sqrt1_2) - dp;
    ddq = std::exp(-0.5e+0 * dx * dx) / 2.506628274631000e+0;
    dx  = dx + dq / ddq;
    }


  dx = ( ( p <= 0.5 ) ? ( -dx ) : ( dx ) );

  return dx;
}
