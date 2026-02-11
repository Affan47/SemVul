IsSameColorSpace( PhotometricInterpretation const &pi ) const
{
  if( PIField == pi ) return true;


  if( PIField == RGB
   || PIField == YBR_RCT
   || PIField == YBR_ICT )
    {
    if( pi == RGB || pi == YBR_RCT || pi == YBR_ICT ) return true;
    }

  if( PIField == YBR_FULL
   || PIField == YBR_FULL_422 )
    {
    if( pi == YBR_FULL || pi == YBR_FULL_422 ) return true;
    }

  return false;
}
