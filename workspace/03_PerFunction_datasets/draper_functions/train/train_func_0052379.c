agx_decode_version(int vercode)
{
  if (vercode&1)
    if (vercode==3201) ver=4;
    else ver=2;
  else
    if (vercode<10000) ver=1;
    else ver=3;
  switch(vercode&(~1))
    {
    case 0000: return AGT10;
    case 1800: return AGT118;
    case 1900: return AGT12;
    case 2000: return AGT12;
    case 3200: return AGTCOS;
    case 3500: return AGT135;
    case 5000: return AGT15;
    case 5050: return AGT15F;
    case 5070: return AGT16;
    case 8200: return AGT182;
    case 8300: return AGT183;
    case 8350: return AGT183;
    case 10000:return AGTME10;
    case 10050:return AGTME10A;
    case 15000:return AGTME15;
    case 15500:return AGTME155;
    case 16000:return AGTME16;
    case 20000:return AGX00;
    default:agtwarn("Unrecognize AGT version",0);
      return 0;
    }
}
