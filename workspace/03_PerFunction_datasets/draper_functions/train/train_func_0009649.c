setKinematics(DipoleSplittingInfo& split) const {

  Lorentz5Momentum emitter = split.splitEmitter()->momentum();
  Lorentz5Momentum emission = split.emission()->momentum();
  Lorentz5Momentum spectator = split.splitSpectator()->momentum();

  split.splittingKinematics(const_cast<IFLightKinematics*>(this));

  Energy2 scale = 2.*(emission*emitter - emission*spectator + emitter*spectator);
  split.scale(sqrt(scale));

  double x =
    scale / (2.*(emitter*emission + emitter*spectator));
  double u = emitter*emission / (emitter*emission + emitter*spectator);

  split.lastPt(split.scale() * sqrt(u*(1.-u)*(1.-x)));
  split.lastZ(u+x*(1.-u));

  split.hardPt(split.lastPt());

  if ( split.hardPt() > IRCutoff() ) {
    split.continuesEvolving();
  } else {
    split.didStopEvolving();
  }

  return 1./(2.*x*(emitter*emission));

}
