set_sig_u_aniso_orth( const Sig_U_aniso_orth& s )
{
  WhatIsSet &= ~ASET_Anis_tFSigma;
  if ( !s.is_null() ) {
    su11 = s(0,0); su22 = s(1,1); su33 = s(2,2);
    su12 = s(0,1); su13 = s(0,2); su23 = s(1,2);
    WhatIsSet |= ASET_Anis_tFSigma;
  }
}
