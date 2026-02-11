invresolsq( const int& index ) const
{
  if ( cell_matches_parent )
    return base_hkl_info().invresolsq(index);
  else
    return base_hkl_info().hkl_of(index).invresolsq(base_cell());
}
