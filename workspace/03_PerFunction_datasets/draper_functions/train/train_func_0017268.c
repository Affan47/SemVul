fireArray( const int size, double* vect,
                           double mean, double stdDev )
{
  for( double* v = vect; v != vect + size; ++v )
    *v = fire( mean, stdDev );
}
