follow( unsigned long start )
{
  std::vector<unsigned long> chain;

  if( start >= count() ) return chain;

  unsigned long p = start;
  while( p < count() )
  {
    if( p == (unsigned long)Eof ) break;
    if( p == (unsigned long)Bat ) break;
    if( p == (unsigned long)MetaBat ) break;
    if( p >= count() ) break;
    chain.push_back( p );
    if( data[p] >= count() ) break;
    p = data[ p ];
  }

  return chain;
}
