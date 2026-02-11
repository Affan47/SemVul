isBad( const SequenceStatistics& s ){
  if( s.letterCount <= 0 ) return true;
  if( s.sequenceCount <= 0 ) return true;
  if( s.alphabet.size() == 0 ) return true;
  if( s.letterProbs.size() != s.alphabet.size() ) return true;

  for( unsigned i = 0; i < s.letterProbs.size(); ++i ){
    if( s.letterProbs[i] < 0 ) return true;
  }

  for( unsigned i = 0; i < s.letterProbs.size(); ++i ){
    if( s.letterProbs[i] > 0 ) return false;
  }

  return true;
}
