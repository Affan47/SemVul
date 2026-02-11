operator>>( std::istream& s, Alphabet& a ){
  s >> a.letters;
  if( s ) a.init();
  return s;
}
