spectranet_trap( libspectrum_word port, libspectrum_byte data )
{
  if( trap_write_msb )
    spectranet_programmable_trap =
      (spectranet_programmable_trap & 0x00ff) | (data << 8);
  else
    spectranet_programmable_trap =
      (spectranet_programmable_trap & 0xff00) | data;

  trap_write_msb = !trap_write_msb;
}
