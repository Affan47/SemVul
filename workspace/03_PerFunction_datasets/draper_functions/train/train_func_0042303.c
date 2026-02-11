SetDimension(unsigned int idx, unsigned int dim)
{

  assert( NumberOfDimensions );
  assert( idx < NumberOfDimensions );
  Dimensions.resize( 3  );


  Dimensions[idx] = dim;
  if( NumberOfDimensions == 2 )
    {
    Dimensions[2] = 1;
    }
}
