check() {
  if ( theDipoles.begin() == prior(theDipoles.end()) ) {
    if ( theDipoles.front().leftParticle()->hasColour() &&
	 theDipoles.front().leftParticle()->hasAntiColour() ) {
      assert(theDipoles.front().rightParticle()->hasColour() &&
	     theDipoles.front().rightParticle()->hasAntiColour());
      ggSingleDipole = true;
    }
  }
}
