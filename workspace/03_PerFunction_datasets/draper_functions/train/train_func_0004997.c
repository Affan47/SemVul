delete_block( libspectrum_rzx *rzx, size_t where )
{
  libspectrum_rzx_iterator it;

  it = get_block( rzx, where );
  if( !it ) {
    fprintf( stderr, "%s: not enough blocks in RZX file\n", progname );
    return 1;
  }

  libspectrum_rzx_iterator_delete( rzx, it );

  return 0;
}
