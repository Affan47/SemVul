intersection_size( const atomList_t &alist ) const
{
  size_t isize = 0;
  for( size_t i = 0; i < alist.size(); ++i )
    if( find( alist.atom( i ) ) ) ++isize;
  return( isize );
}
