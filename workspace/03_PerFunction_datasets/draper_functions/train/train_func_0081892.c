init( const Grid_sampling& grid_sam, const FFTtype type )
{
  type_ = type;
  if ( type_ == Default ) type_ = default_type();


  grid_real_ = grid_sam;
  grid_reci_ = Grid( grid_real_.nu(), grid_real_.nv(), grid_real_.nw()/2+1 );


  std::complex<ffttype>* fillptr = NULL;
  row_kl.resize( grid_reci_.nv(), grid_reci_.nw(), fillptr );
  ffttype* rfillptr = NULL;
  row_uv.resize( grid_real_.nu(), grid_real_.nv(), rfillptr );
}
