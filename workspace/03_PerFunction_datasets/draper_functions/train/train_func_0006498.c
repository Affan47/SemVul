single_reg( int i, enum hl_type use_hl, libspectrum_byte offset,
	    char *buffer, size_t buflen )
{
  char buffer2[40];

  if( i == 0x04 && use_hl != USE_HL ) {
    snprintf( buffer, buflen, "%sh", hl_ix_iy( use_hl ) );
    return 0;
  } else if( i == 0x05 && use_hl != USE_HL ) {
    snprintf( buffer, buflen, "%sl", hl_ix_iy( use_hl ) );
    return 0;
  } else if( i == 0x06 && use_hl != USE_HL ) {
    ix_iy_offset( buffer2, 40, use_hl, offset );
    snprintf( buffer, buflen, "%s", buffer2 );
    return 1;
  } else {
    const char *regs[] = { "B", "C", "D", "E", "H", "L", "(HL)", "A" };
    snprintf( buffer, buflen, "%s", regs[i] );
    return 0;
  }
}
