decay(ClusterVector & clusters, tPVector & finalhadrons) {


  vector<tClusterPtr> redefinedClusters;

  for (ClusterVector::const_iterator it = clusters.begin();
       it != clusters.end(); ++it) {


    if ( ! (*it)->isAvailable()  ||  ! (*it)->isReadyToDecay() ) continue;


    if ( (*it)->numComponents() != 2 ) {
      generator()->logWarning( Exception("LightClusterDecayer::decay "
					 "***Still cluster with not exactly"
					 " 2 components*** ",
					 Exception::warning) );
      continue;
    }


    tPPtr ptrQ1 = (*it)->particle(0);
    tPPtr ptrQ2 = (*it)->particle(1);

     tcPDPtr par1 = ptrQ1->dataPtr();
     tcPDPtr par2 = ptrQ2->dataPtr();


     Energy threshold = _hadronSelector->massLightestHadronPair(par1,par2);

     if (CheckId::isExotic(par1,par2))
       threshold *= (1.0 + UseRandom::rnd()*_limExotic);
     else if (CheckId::hasBottom(par1,par2))
       threshold *= (1.0 + UseRandom::rnd()*_limBottom);
     else if (CheckId::hasCharm(par1,par2))
       threshold *= (1.0 + UseRandom::rnd()*_limCharm);


    if((*it)->mass()>=threshold) continue;

    tcPDPtr hadron= _hadronSelector->lightestHadron(par1,par2);


    multimap<Length,tClusterPtr> candidates;
    for ( ClusterVector::iterator jt = clusters.begin();
	  jt != clusters.end(); ++jt ) {
      if ((*jt)->isAvailable() && (*jt)->isReadyToDecay() && jt != it) {
	Length distance = abs (((*it)->vertex() - (*jt)->vertex()).m());
	candidates.insert(pair<Length,tClusterPtr>(distance,*jt));
      }
    }


    multimap<Length,tClusterPtr>::const_iterator mmapIt = candidates.begin();
    bool found = false;
    while (!found && mmapIt  != candidates.end()) {
      found = reshuffling(hadron, *it, (*mmapIt).second, redefinedClusters, finalhadrons);
      if (!found) ++mmapIt;
    }

    if (!found) return partonicReshuffle(hadron,*it,finalhadrons);
  }


  for (tClusterVector::const_iterator it = redefinedClusters.begin();
       it != redefinedClusters.end(); ++it) {
    clusters.push_back(*it);
  }
  return true;
 }
