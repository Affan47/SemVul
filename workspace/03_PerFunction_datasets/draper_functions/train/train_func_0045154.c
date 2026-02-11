disciple_memory_map( void )
{
  struct memory_page *rom_page, *lower_page, *upper_page;

  if( !disciple_active ) return;


  rom_page = disciple_memory_map_romcs_rom;

  if( !disciple_memswap ) {
    lower_page = rom_page;
    upper_page = disciple_memory_map_romcs_ram;
  } else {
    lower_page = disciple_memory_map_romcs_ram;
    upper_page = rom_page;
  }

  memory_map_romcs_8k( 0x0000, lower_page );
  memory_map_romcs_8k( 0x2000, upper_page );
}
