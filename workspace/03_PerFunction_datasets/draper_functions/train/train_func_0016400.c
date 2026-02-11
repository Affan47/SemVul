vl_pgm_extract_data (FILE* f, VlPgmImage const *im, void *data)
{
  int bpp       = vl_pgm_get_bpp       (im) ;
  int data_size = vl_pgm_get_npixels (im) ;
  int c ;
  vl_bool good = 1 ;

  VlThreadSpecificState * threadState = vl_get_thread_specific_state() ;


  if (im->is_raw) {

    c = fread( data,
               bpp,
               data_size,
               f ) ;
    good = (c == data_size) ;


#if defined(VL_ARCH_LITTLE_ENDIAN)
    if (bpp == 2) {
      int i ;
      vl_uint8 *pt = (vl_uint8*) data ;
      for(i = 0 ; i < 2 * data_size ; i += 2) {
        vl_uint8 tmp = pt [i] ;
        pt [i]   = pt [i+1] ;
        pt [i+1] = tmp ;
      }
    }
#endif
  }


  else {
    int i ;
    int unsigned v ;
    for(good = 1, i = 0 ;
        i < data_size && good ;
        ++i) {
      c = fscanf(f, " %ud", &v) ;
      if (bpp == 1) {
        * ((vl_uint8* )  data + i) = (vl_uint8)  v ;
      } else {
        * ((vl_uint16*)  data + i) = (vl_uint16) v ;
      }
      good &= c == 1 ;
    }
  }

  if(! good ) {
    snprintf(threadState->lastErrorMessage, VL_ERR_MSG_LEN,
             "Invalid PGM data") ;
    return (threadState->lastError = VL_ERR_PGM_INV_DATA) ;
  }
  return 0 ;
}
