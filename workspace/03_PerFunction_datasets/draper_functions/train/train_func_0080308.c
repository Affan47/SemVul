init( const Spacegroup& spacegroup, const Cell& cell, const Resolution& resolution, const bool& generate )
{

  spacegroup_ = spacegroup;
  cell_ = cell;
  resolution_ = resolution;


  if ( is_null() ) return;


  Grid g( 24, 24, 24 );
  isymop.resize( spacegroup_.num_symops() );
  for ( int sym = 0; sym < spacegroup_.num_symops(); sym++ )
    isymop[sym] = Isymop( spacegroup_.symop(sym), g );


  hkl.clear();
  if ( generate ) generate_hkl_list();
  update_hkl_list();
}
