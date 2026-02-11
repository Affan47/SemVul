_setChildren(ClusterVector clusters) const {


  tPVector partons;
  for (ClusterVector::const_iterator cl = clusters.begin();
       cl != clusters.end(); cl++) {
    partons.push_back( (*cl)->colParticle() );
    partons.push_back( (*cl)->antiColParticle() );
  }
  for_each(partons.begin(), partons.end(), mem_fun(&Particle::undecay));


  for (ClusterVector::iterator cl = clusters.begin();
       cl != clusters.end(); cl++) {
    (*cl)->colParticle()->addChild(*cl);
    (*cl)->antiColParticle()->addChild(*cl);
  }

}
