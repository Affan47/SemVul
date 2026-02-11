_doRecoStatistical(ClusterVector & cv) const {

  const size_t nclusters = cv.size();


  ParticleVector q, aq;
  for (size_t i = 0; i < nclusters; i++) {
    q.push_back( cv.at(i)->colParticle() );
    aq.push_back( cv.at(i)->antiColParticle() );
  }


  Energy2 t, delta;
  Energy2 lambda = _clusterMassSum(q,aq);
  const unsigned _ntries = _triesPerStepFactor * nclusters;


  {
    vector<Energy2> typical;
    for (int i = 0; i < 10; i++) {
      const pair <int,int> toswap = _shuffle(q,aq,5);
      ParticleVector newaq = aq;
      swap (newaq[toswap.first], newaq[toswap.second]);
      Energy2 newlambda = _clusterMassSum(q,newaq);
      typical.push_back( abs(newlambda - lambda) );
    }
    t = _initTemp * Math::median(typical);
  }


  for (unsigned step = 0; step < _annealingSteps; step++) {


    unsigned nSuccess = 0;
    for (unsigned it = 0; it < _ntries; it++) {


      const unsigned maxtries = 10;
      const pair <int,int> toswap = _shuffle(q,aq,maxtries);
      const int i = toswap.first;
      const int j = toswap.second;


      if (i == -1) break;


      ParticleVector newaq = aq;
      swap (newaq[i], newaq[j]);


      Energy2 newlambda = _clusterMassSum(q,newaq);
      delta = newlambda - lambda;
      double prob = 1.0;
      if (delta > ZERO) prob = ( abs(t) < 1e-8*MeV2 ) ? 0.0 : exp(-delta/t);
      if (UseRandom::rnd() < prob) {
        lambda = newlambda;
        swap (newaq, aq);
        nSuccess++;
      }
    }
    if (nSuccess == 0) break;


    t *= _annealingFactor;
  }


  ClusterVector newclusters;
  for (size_t i = 0; i < nclusters; i++) {
    ClusterPtr cl = new_ptr( Cluster( q.at(i), aq.at(i) ) );
    newclusters.push_back(cl);
  }
  swap(newclusters,cv);
  return;
}
