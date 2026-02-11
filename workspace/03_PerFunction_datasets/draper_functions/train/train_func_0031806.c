set_u_iso( const ftype& v )
{
  WhatIsSet &= ~ASET_tempFactor;
  if ( !Util::is_nan( v ) ) {
    tempFactor = Util::u2b(v);
    WhatIsSet |= ASET_tempFactor;
  }
}
