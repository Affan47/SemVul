getBestMapping( vector<Vector2D> &targetPos,
				vector<Vector2D> &relPosForFighters ) {

  int actPerm[nrInvolved];
  vector<Vector2D> *bestMapping = new vector<Vector2D>();
  vector<Vector2D> *testMapping = new vector<Vector2D>();
  for ( int i = 0; i < nrInvolved; i++ ) {
    bestMapping->push_back( Vector2D( 0,0 ) );
    testMapping->push_back( Vector2D( 0,0 ) );
    actPerm[ i ] = i;
  }
  float mapCost = 1000000;

  int nrPerm = factorial( nrInvolved );

  for ( int perm = 0; perm < nrPerm; perm++ ) {
    calcNextPerm( actPerm );
    float testMappingCost = calcTestMapping( actPerm, targetPos, testMapping );
    if ( mapCost > testMappingCost ) {
      vector<Vector2D> *tmpMapping = bestMapping;
      bestMapping = testMapping;
      testMapping = tmpMapping;
      mapCost = testMappingCost;
    }
  }

  for ( int e = 0; e < nrInvolved; e++ ) {
    relPosForFighters.push_back( (*bestMapping)[e] );
  }
  delete bestMapping;
  delete testMapping;
}
