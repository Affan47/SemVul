ptzAllowed(pair<Energy,double> ptz) const {

  assert( lastScale() == (bornEmitterMomentum()+bornSpectatorMomentum()).m() );

  double mui2 = sqr( realEmitterData()->mass() / lastScale() );
  double mu2  = sqr( realEmissionData()->mass() / lastScale() );
  double muj2 = sqr( realSpectatorData()->mass() / lastScale() );

  Energy pt = ptz.first;
  double z = ptz.second;

  double y = ( sqr( pt / lastScale() ) + sqr(1.-z)*mui2 + z*z*mu2 ) /
      (z*(1.-z)*(1.-mui2-mu2-muj2));


  double bar = 1.-mui2-mu2-muj2;
  double ym = 2.*sqrt(mui2)*sqrt(mu2)/bar;
  double yp = 1. - 2.*sqrt(muj2)*(1.-sqrt(muj2))/bar;
  double zm = ( (2.*mui2+bar*y)*(1.-y) - sqrt(y*y-ym*ym)*sqrt(sqr(2.*muj2+bar-bar*y)-4.*muj2) ) /
    ( 2.*(1.-y)*(mui2+mu2+bar*y) );
  double zp = ( (2.*mui2+bar*y)*(1.-y) + sqrt(y*y-ym*ym)*sqrt(sqr(2.*muj2+bar-bar*y)-4.*muj2) ) /
    ( 2.*(1.-y)*(mui2+mu2+bar*y) );

  if ( y<ym || y>yp || z<zm || z>zp ) return false;
  return true;
}
