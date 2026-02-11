canHandle(const cPDVector& partons,
			    int emitter, int emission, int spectator) const {
  return
    emitter < 2 && spectator > 1 &&
    abs(partons[emission]->id()) < 6 &&
    abs(partons[emitter]->id()) < 6 &&
    partons[emission]->id() - partons[emitter]->id() == 0 &&
    partons[emitter]->mass() == ZERO &&
    partons[emission]->mass() == ZERO &&
    partons[spectator]->mass() == ZERO;
}
