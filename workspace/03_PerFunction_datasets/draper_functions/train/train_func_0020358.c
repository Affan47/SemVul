subVector ( vector<int> vec, int start, int end )
{
  vector<int> retour;
  if ( start > end ) {
    cerr << "ERREUR : TERcalc::subVector : end > start" << endl;
    exit ( 0 );
  }
  for ( int i = start; ( ( i < end ) && ( i < ( int ) vec.size() ) ); i++ ) {
    retour.push_back ( vec.at ( i ) );
  }
  return retour;
}
