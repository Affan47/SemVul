setSeed( unsigned int seed )
{
  if ( seed == 0 )
    srand( (unsigned int) time(NULL) );
  else
    srand( seed );
}
