me2() const {

  if ( jacobian() == 0.0 )
    return 0.0;

  double x = subtractionParameters()[0];
  double z = subtractionParameters()[1];

  Energy2 prop =
    2.*((realEmissionME()->lastXComb().meMomenta()[realEmitter()])*
	(realEmissionME()->lastXComb().meMomenta()[realEmission()]))*x;

  double CF = (SM().Nc()*SM().Nc()-1.)/(2.*SM().Nc());

  double res =
    8.*Constants::pi*CF*(realEmissionME()->lastXComb().lastSHat())*
    (realEmissionME()->lastXComb().lastAlphaS())/prop;

  res *= ( 2./(1.-z+(1.-x)) -(1.+z) +(1.-x)*(1.+3.*x*z) );

  res *= -underlyingBornME()->colourCorrelatedME2(make_pair(bornEmitter(),bornSpectator()));

  res *=
    pow(realEmissionME()->lastXComb().lastSHat() / underlyingBornME()->lastXComb().lastSHat(),
	underlyingBornME()->lastXComb().mePartonData().size()-4.);

  res *=
    realEmissionME()->finalStateSymmetry() /
    underlyingBornME()->finalStateSymmetry();

  lastME2(res);

  logME2();

  return res;

}
