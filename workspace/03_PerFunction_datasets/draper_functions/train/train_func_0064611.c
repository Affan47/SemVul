set_sig_occupancy( const ftype& s )
{
  WhatIsSet &= ~ASET_OccSigma;
  if ( !Util::is_nan( s ) ) {
    sigOcc = s;
    WhatIsSet |= ASET_OccSigma;
  }
}
