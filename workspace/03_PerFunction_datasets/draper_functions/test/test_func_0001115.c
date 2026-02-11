compare( const matrix3x3 & m1, const matrix3x3 & m2 )
{
  bool ret = true;
  for( int i = 0; i < 3; i++ )
    ret &= compare( m1.GetColumn(i), m2.GetColumn(i) );
  return ret;
}
