generateSplitting(double kappa, double xi, double rphi,
					  DipoleSplittingInfo& info) {

  Energy pt = IRCutoff() * pow(0.5 * generator()->maximumCMEnergy()/IRCutoff(),kappa);

  if ( pt > info.hardPt() ) {
    jacobian(0.0);
    return false;
  }

  double z;
  double mapZJacobian;

  if ( info.index().emitterData()->id() == ParticleID::g ) {
    if ( info.emissionData()->id() != ParticleID::g ) {
      z = xi;
      mapZJacobian = 1.;
    } else {
      z = exp(xi)/(1.+exp(xi));
      mapZJacobian = z*(1.-z);
    }
  } else {
    z = 1.-exp(-xi);
    mapZJacobian = 1.-z;
  }

  double s = z*(1.-z);
  double zp = 0.5*(1.+sqrt(1.-sqr(pt/info.hardPt())));
  double zm = 0.5*(1.-sqrt(1.-sqr(pt/info.hardPt())));

  if ( pt < IRCutoff() ||
       pt > info.hardPt() ||
       z > zp || z < zm ) {
    jacobian(0.0);
    return false;
  }

  double phi = 2.*Constants::pi*rphi;

  jacobian( 2. * mapZJacobian * (1. - sqr(pt) / (s * sqr(info.scale())) ) *
	    log(0.5 * generator()->maximumCMEnergy()/IRCutoff()) );

  lastPt(pt);
  lastZ(z);
  lastPhi(phi);

  if ( theMCCheck )
    theMCCheck->book(1.,1.,info.scale(),info.hardPt(),pt,z,jacobian());

  return true;

}
