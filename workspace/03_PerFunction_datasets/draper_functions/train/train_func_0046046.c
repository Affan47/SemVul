specplus2a_reset( void )
{
  int error;

  error = machine_load_rom( 0, settings_current.rom_plus2a_0,
                            settings_default.rom_plus2a_0, 0x4000 );
  if( error ) return error;
  error = machine_load_rom( 1, settings_current.rom_plus2a_1,
                            settings_default.rom_plus2a_1, 0x4000 );
  if( error ) return error;
  error = machine_load_rom( 2, settings_current.rom_plus2a_2,
                            settings_default.rom_plus2a_2, 0x4000 );
  if( error ) return error;
  error = machine_load_rom( 3, settings_current.rom_plus2a_3,
                            settings_default.rom_plus2a_3, 0x4000 );
  if( error ) return error;

  error = specplus3_plus2a_common_reset();
  if( error ) return error;

  periph_clear();
  machines_periph_plus3();
  periph_update();

  spec48_common_display_setup();

  return 0;
}
