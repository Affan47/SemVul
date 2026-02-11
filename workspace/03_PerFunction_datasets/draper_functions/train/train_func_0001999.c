setChain( std::vector<unsigned long> chain )
{
  if( chain.size() )
  {
    for( unsigned i=0; i<chain.size()-1; i++ )
      set( chain[i], chain[i+1] );
    set( chain[ chain.size()-1 ], AllocTable::Eof );
  }
}
