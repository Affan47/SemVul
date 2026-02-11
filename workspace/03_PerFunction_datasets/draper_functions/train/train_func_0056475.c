cut(stack<ClusterPtr> & clusterStack,
   			   ClusterVector &clusters, tPVector & finalhadrons,
			   bool softUEisOn) {


  while (!clusterStack.empty()) {

    ClusterPtr iCluster = clusterStack.top(); clusterStack.pop();

    cutType ct = cut(iCluster, finalhadrons, softUEisOn);

    if(!ct.first.first || !ct.second.first) {

      if(iCluster->isBeamCluster() && softUEisOn)
	iCluster->isAvailable(false);
      continue;
    }

    ClusterPtr one = dynamic_ptr_cast<ClusterPtr>(ct.first.first);
    ClusterPtr two = dynamic_ptr_cast<ClusterPtr>(ct.second.first);

    if(iCluster->isBeamCluster() && (!one||!two) && softUEisOn) {
      iCluster->isAvailable(false);
      continue;
    }


    assert(ct.first.second && ct.second.second);

    iCluster->addChild(ct.first.first);


    iCluster->addChild(ct.second.first);


    if(one) {
      clusters.push_back(one);
      if(one->isBeamCluster() && softUEisOn)
	one->isAvailable(false);
      if(isHeavy(one) && one->isAvailable())
	clusterStack.push(one);
    }
    if(two) {
      clusters.push_back(two);
      if(two->isBeamCluster() && softUEisOn)
	two->isAvailable(false);
      if(isHeavy(two) && two->isAvailable())
	clusterStack.push(two);
    }
  }
}
