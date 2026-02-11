GetIndex(VRType vr)
{
  if( vr == VR::VL32 ) return 0;
  int l;
  assert( vr <= VR_END );
  switch(vr)
    {
  case INVALID:
    l = 0;
    break;
  case OB_OW:
    l =  28;
    break;
  case US_SS:
    l =  29;
    break;
  case US_SS_OW:
    l =  30;
    break;
  case VR_END:
    l = 31;
    break;
  default:
      {
      int a = (int)vr;
      for (l = 0; a > 1; ++l)
        a >>= 1;
      l++;
      }
    }
  return l;
}
