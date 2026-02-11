fits_read_rgnfile( const char *filename,
            WCSdata    *wcs,
            SAORegion  **Rgn,
            int        *status )


{
  fitsfile *fptr;
  int tstatus = 0;

  if( *status ) return( *status );


  fits_write_errmark();
  if ( ffopen(&fptr, filename, READONLY, &tstatus) ) {
    fits_clear_errmark();
    fits_read_ascii_region(filename, wcs, Rgn, status);
  } else {
    fits_read_fits_region(fptr, wcs, Rgn, status);
  }

  return(*status);

}
