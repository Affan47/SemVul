isAllowableMACType(E_MACType macType) const
{
  OFBool result = OFFalse;
  switch (macType)
  {
    case EMT_RIPEMD160:
    case EMT_SHA1:
    case EMT_MD5:
      result = OFTrue;
      break;
    default:

      break;
  }
  return result;
}
