diameter( void ) const
{
  unsigned result = 0;
  for( unsigned i = 0; i < dimension_; ++i )
    result = (number_[i] > result ? number_[i] : result);
  return( result );
}
