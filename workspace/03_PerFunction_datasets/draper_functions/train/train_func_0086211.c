tc2048_port_from_ula( libspectrum_word port )
{

  port &= 0xff;

  return( port == 0xf4 || port == 0xfe || port == 0xff );
}
