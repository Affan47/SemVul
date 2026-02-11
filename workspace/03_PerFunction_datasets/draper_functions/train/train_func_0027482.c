_reconnect(ClusterPtr c1, ClusterPtr c2) const {


  ClusterPtr newCluster1
    = new_ptr( Cluster( c1->colParticle(), c2->antiColParticle() ) );
  ClusterPtr newCluster2
    = new_ptr( Cluster( c2->colParticle(), c1->antiColParticle() ) );

  return pair <ClusterPtr,ClusterPtr> (newCluster1, newCluster2);
}
