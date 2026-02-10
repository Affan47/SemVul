port_mdr_in( void )
{
  libspectrum_byte ret = 0xff;
  int m;

  for( m = 0; m < 8; m++ ) {

    microdrive_t *mdr = &microdrive[ m ];

    if( mdr->motor_on && mdr->inserted ) {

      if( mdr->transfered < mdr->max_bytes ) {
	mdr->last = libspectrum_microdrive_data( mdr->cartridge,
						   mdr->head_pos );
	increment_head( m );
      }

      mdr->transfered++;
      ret &= mdr->last;
    }

  }

  return ret;
}
