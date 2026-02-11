beta_sp_write( libspectrum_word port GCC_UNUSED, libspectrum_byte b )
{
  if( !beta_active ) return;


  beta_select_drive( b & 0x03 );

  wd_fdc_set_hlt( beta_fdc, ( ( b & 0x08 ) ? 1 : 0 ) );
  fdd_set_head( &beta_fdc->current_drive->fdd, ( ( b & 0x10 ) ? 0 : 1 ) );

  beta_fdc->dden = b & 0x20 ? 1 : 0;

  beta_system_register = b;
}
