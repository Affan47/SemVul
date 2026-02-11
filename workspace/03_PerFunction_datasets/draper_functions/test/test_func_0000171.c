uc_width (ucs4_t uc, const char *encoding)
{

  if ((uc >> 9) < 240)
    {
      int ind = nonspacing_table_ind[uc >> 9];
      if (ind >= 0)
	if ((nonspacing_table_data[64*ind + ((uc >> 3) & 63)] >> (uc & 7)) & 1)
	  {
	    if (uc > 0 && uc < 0xa0)
	      return -1;
	    else
	      return 0;
	  }
    }
  else if ((uc >> 9) == (0xe0000 >> 9))
    {
      if (uc >= 0xe0100)
	{
	  if (uc <= 0xe01ef)
	    return 0;
	}
      else
	{
	  if (uc >= 0xe0020 ? uc <= 0xe007f : uc == 0xe0001)
	    return 0;
	}
    }


  if (uc >= 0x1100
      && ((uc < 0x1160)
	  || (uc >= 0x2329 && uc < 0x232b)
	  || (uc >= 0x2e80 && uc < 0xa4d0
	      && !(uc == 0x303f) && !(uc >= 0x4dc0 && uc < 0x4e00))
	  || (uc >= 0xac00 && uc < 0xd7a4)
	  || (uc >= 0xf900 && uc < 0xfb00)
	  || (uc >= 0xfe10 && uc < 0xfe20)
	  || (uc >= 0xfe30 && uc < 0xfe70)
	  || (uc >= 0xff00 && uc < 0xff61)
	  || (uc >= 0xffe0 && uc < 0xffe7)
	  || (uc >= 0x20000 && uc <= 0x2a6d6)
	  || (uc >= 0x2f800 && uc <= 0x2fa1d)
     )   )
    return 2;


  if (uc >= 0x00A1 && uc < 0xFF61 && uc != 0x20A9
      && is_cjk_encoding (encoding))
    return 2;
  return 1;
}
