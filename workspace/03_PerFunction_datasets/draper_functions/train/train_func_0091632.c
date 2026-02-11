xsh_mark_tell( cpl_frame *s1d_frame, cpl_frame *tellmask_frame)
{
  xsh_spectrum *s1d = NULL;
  int *qual = NULL;
  int size;
  cpl_vector *tellmask_vect = NULL;
  int tellmask_size, i;
  const char *s1d_name = NULL;
  const char *tag = NULL;
  cpl_frame *result = NULL;

  XSH_ASSURE_NOT_NULL( s1d_frame);

  check( tag = cpl_frame_get_tag( s1d_frame));
  check( s1d_name = cpl_frame_get_filename( s1d_frame));

  check( s1d = xsh_spectrum_load( s1d_frame));
  check( qual = xsh_spectrum_get_qual( s1d));
  check( size = xsh_spectrum_get_size( s1d));

  if ( tellmask_frame != NULL){
    const char* tellmask_name = NULL;

    check( tellmask_name = cpl_frame_get_filename( tellmask_frame));
    xsh_msg("Use telluric mask %s", tellmask_name);

    check( tellmask_vect = cpl_vector_load( tellmask_name, 0));
    check( tellmask_size = cpl_vector_get_size( tellmask_vect));

    XSH_ASSURE_NOT_ILLEGAL( tellmask_size == size);

    for( i=0; i< size; i++){
      double mask_val;

      mask_val = cpl_vector_get( tellmask_vect, i);

      if ( mask_val > 0){
        qual[i] |= QFLAG_TELLURIC_UNCORRECTED;
      }
    }
    check( result = xsh_spectrum_save( s1d, s1d_name, tag));
  }
  else{
    xsh_msg("No telluric mask");
  }

  cleanup:
    xsh_free_frame( &result);
    xsh_spectrum_free( &s1d);
    xsh_free_vector( &tellmask_vect);
}
