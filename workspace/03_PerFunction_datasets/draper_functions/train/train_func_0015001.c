fmf_read_slice_blokk( libspectrum_byte *scrl, int w, int h )
{
  int last = -1, d = -1, width = w, len = 0, i;
  libspectrum_byte *scrp;

  for( ; h > 0; h--, scrl += SCR_PITCH ) {
    scrp = scrl;
    w = width;
    while( w > 0 ) {
      if( len == 0 ) {
        if( ( d = fgetc_compr( inp_file ) ) == -1 ) {
          printe( "\n\nCorrupt input file ($) @0x%08lx.\n", (unsigned long)ftell( inp_file ) );
          return ERR_CORRUPT_INP;
        }
        if( d == last ) {
	  if( ( len = fgetc_compr( inp_file ) ) == -1 ) {
	    printe( "\n\nCorrupt input file ($) @0x%08lx.\n", (unsigned long)ftell( inp_file ) );
	    return ERR_CORRUPT_INP;
	  }
	  len++;
	  last = -1;
        } else {
	  len = 1, last = d;
        }
      }
      if( len > w ) i = w; else i = len;
      len -= i;
      w -= i;
      for(; i > 0; i-- )
        *scrp++ = d;
    }
  }
  return 0;
}
