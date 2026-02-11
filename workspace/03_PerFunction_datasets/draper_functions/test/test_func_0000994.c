init_scalers( void )
{
  scaler_register_clear();

  scaler_register( SCALER_NORMAL );
  scaler_register( SCALER_DOUBLESIZE );
  scaler_register( SCALER_TRIPLESIZE );
  scaler_register( SCALER_2XSAI );
  scaler_register( SCALER_SUPER2XSAI );
  scaler_register( SCALER_SUPEREAGLE );
  scaler_register( SCALER_ADVMAME2X );
  scaler_register( SCALER_ADVMAME3X );
  scaler_register( SCALER_DOTMATRIX );
  scaler_register( SCALER_PALTV );
  scaler_register( SCALER_HQ2X );
  if( machine_current->timex ) {
    scaler_register( SCALER_HALF );
    scaler_register( SCALER_HALFSKIP );
    scaler_register( SCALER_TIMEXTV );
    scaler_register( SCALER_TIMEX1_5X );
  } else {
    scaler_register( SCALER_TV2X );
    scaler_register( SCALER_TV3X );
    scaler_register( SCALER_PALTV2X );
    scaler_register( SCALER_PALTV3X );
    scaler_register( SCALER_HQ3X );
  }

  if( scaler_is_supported( current_scaler ) ) {
    scaler_select_scaler( current_scaler );
  } else {
    scaler_select_scaler( SCALER_NORMAL );
  }
}
