canHandle(const DipoleIndex& ind) const {
  return
    abs(ind.emitterData()->id()) < 6  &&
    ind.emitterData()->mass() == ZERO &&
    ind.spectatorData()->mass() == ZERO &&
    ind.initialStateEmitter() && ind.initialStateSpectator();
}
