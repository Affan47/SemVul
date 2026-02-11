analyze(tEventPtr event, long, int, int) {


  Lorentz5Momentum pg;
  bool foundphoton = false;
  set<tcPPtr> particles;
  event->selectFinalState(inserter(particles));

  for(set<tcPPtr>::const_iterator it = particles.begin();
      it != particles.end(); ++it) {
    if((**it).id()==ParticleID::gamma) {

      if( (**it).momentum().perp() > pg.perp() ) {
	foundphoton = true;
	pg=getMomentum(*it);
      }
    }
  }

  if (foundphoton) {
    Energy pt = pg.perp();
    (_ptg)+=(pt)/GeV;
    (_Eg)+=pg.e()/GeV;
    (_ptgZoom)+=(pt)/GeV;
    double rap = 0.5*log((pg.e()+pg.z())/(pg.e()-pg.z()));
    (_rapg)+=(rap);
    (_phig)+=pg.phi();
  } else {
    cerr << "Analysis/GammaJetAnalysis: Found no hard photon in event "
	 << event->number()  << ".\n";
    generator()->log() << "Analysis/GammaJetAnalysis: "
		       << "Found no hard photon in event "
		       << event->number()  << ".\n"
		       << *event;
  }
}
