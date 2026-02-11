feof_compr( FILE *f )
{
  if( fmf_compr ) {
    if( fmf_compr_feof )
      return 1;
    if( zstream.avail_in > 0 || zstream.avail_out != ZBUF_SIZE )
      return 0;
    fmf_compr_feof = feof( f );
    return fmf_compr_feof;
  } else {
    return feof( f );
  }
}
