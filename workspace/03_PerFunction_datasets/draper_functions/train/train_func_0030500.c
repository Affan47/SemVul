setPssm( const ScoreMatrixRow* pssm, size_t qsize, double T,
			  const OneQualityExpMatrix& oqem,
			  const uchar* sequenceBeg, const uchar* qualityBeg ) {
    this->T = T;
    this -> isPssm = true;
    pssmExp.resize( qsize * scoreMatrixRowSize );
    pssmExp2 = reinterpret_cast<ExpMatrixRow*> ( &pssmExp[0] );

    if( oqem ){
      makePositionSpecificExpMatrix( oqem, sequenceBeg, sequenceBeg + qsize,
                                     qualityBeg, &pssmExp[0] );
    }
    else{
      for ( size_t i=0; i<qsize; ++i ) {
        for ( unsigned j=0; j<scoreMatrixRowSize; ++j ) {
          pssmExp2[ i ][ j ] = EXP ( pssm[ i ][ j ] / T );
        }
      }
    }
  }
