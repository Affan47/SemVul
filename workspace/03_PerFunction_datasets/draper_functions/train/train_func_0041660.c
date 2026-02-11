evaluate() const {

  if ( projectionDipole()->verbose() )
    generator()->log() << "'" << name() << "' evaluating\n";

  if ( !projectionDipole()->underlyingBornME()->
       lastXCombPtr()->willPassCuts() )
    return 0.;

  double fscaleFactor =
    projectionDipole()->realEmissionME()->factorizationScaleFactor();

  Energy2 fscale =
    fscaleFactor * (sqr(projectionDipole()->lastPt()) + sqr(theScreeningScale));

  double dummy;
  double ratio = ME2byDipoles::evaluate(dummy);

  Energy2 bornSHat =
    projectionDipole()->underlyingBornME()->lastXComb().lastSHat();
  double bornJacobian =
    projectionDipole()->underlyingBornME()->lastXComb().jacobian();

  if ( projectionDipole()->verbose() )
    generator()->log() << "Born sHat/GeV2 = " << (bornSHat/GeV2)
		       << " Born Jacobian = " << bornJacobian << "\n" << flush;

  CrossSection born =
    sqr(hbarc) * scaledBorn(fscale) * bornJacobian / (2.*bornSHat);

  if ( born == ZERO ) {
    if ( projectionDipole()->verbose() )
      generator()->log() << "'" << name() << "' done evaluating\n";
    return 0.0;
  }

  if ( bornScreening() ) {
    born += sqr(hbarc) * scaledBornScreen() * bornJacobian / (2.*bornSHat);
  }

  ratio *= ( projectionDipole()->dSigHatDR(fscale) / born );

  double rscaleFactor =
    projectionDipole()->realEmissionME()->renormalizationScaleFactor();

  double runAlpha =
    SM().alphaS(rscaleFactor * (sqr(projectionDipole()->lastPt())
				+ sqr(theScreeningScale)));

  if ( projectionDipole()->verbose() )
    generator()->log() << "real emission alpha_s = "
		       << projectionDipole()->realEmissionME()->lastXComb().lastAlphaS()
		       << " pt running alpha_s = " << runAlpha
		       << " from pt/GeV = " << (projectionDipole()->lastPt()/GeV)
		       << "\n" << flush;

  ratio *= runAlpha / projectionDipole()->realEmissionME()->lastXComb().lastAlphaS();

  if ( projectionDipole()->verbose() )
    generator()->log() << "'" << name() << "' done evaluating\n";

  return ratio;

}
