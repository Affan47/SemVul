init( const Spacegroup& spacegroup, const Cell& cell, const Grid_sampling grid_sam, const FFTtype type )
{
  FFTmap_p1::init( grid_sam, type );
  spacegroup_ = spacegroup;
  cell_ = cell;


  isymop.resize( spacegroup.num_symops() );
  for ( int sym = 0; sym < spacegroup.num_symops(); sym++ )
    isymop[sym] = Isymop( spacegroup.symop(sym), grid_sam );
}
