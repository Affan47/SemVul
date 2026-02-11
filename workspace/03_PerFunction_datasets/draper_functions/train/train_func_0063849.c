invariant_under_change_of_hand() const
{
  for ( int k=0; k<nsym; k++ )
    for ( int j=0; j<3; j++ )
      if ( isymops[k].rot()(j,j) == 1 )
	if ( isymops[k].trn()[j] != 0 && isymops[k].trn()[j] != 12 )
	  return false;
  return true;
}
