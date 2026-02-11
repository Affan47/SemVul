traceback_ama( std::vector< SegmentPair >& chunks,
			    double gamma ) const{


    size_t k = bestAntiDiagonal;
    size_t i = bestPos1;
    size_t oldPos1 = i;

    while( k > 2 ){
      const size_t j = k - i - 2;
      const double s = 2 * gamma * cellx( pp, k, i ) - ( mX1[ i ] + mX2[ j ] );
      const double t = gamma * mI[ j ] - mX2[ j ];
      const double u = gamma * mD[ i ] - mX1[ i ];
      const int m =
	maxIndex( diagx( X, k, i ) + s,
                  horix( X, k, i ) + u,
                  vertx( X, k, i ) + t );
      if( m == 0 ){
	k -= 2;
	i -= 1;
      }
      if( (m > 0 && oldPos1 != i) || k == 2 ){
	chunks.push_back( SegmentPair( i, k - i - 2, oldPos1 - i ) );
      }
      if( m > 0 ){
	k -= 1;
	i -= (m == 1);
	oldPos1 = i;
      }
    }
  }
