if2_from_snapshot( libspectrum_snap *snap )
{
  if( !libspectrum_snap_interface2_active( snap ) ) return;

  if2_active = 1;
  machine_current->ram.romcs = 1;

  if( libspectrum_snap_interface2_rom( snap, 0 ) ) {

    if2_memory_map_romcs[0].offset = 0;
    if2_memory_map_romcs[0].page_num = 0;
    if2_memory_map_romcs[0].page =
      memory_pool_allocate( 2 * MEMORY_PAGE_SIZE *
			    sizeof( libspectrum_byte ) );
    if( !if2_memory_map_romcs[0].page ) {
      ui_error( UI_ERROR_ERROR, "Out of memory at %s:%d", __FILE__, __LINE__ );
      return;
    }

    memcpy( if2_memory_map_romcs[0].page,
	    libspectrum_snap_interface2_rom( snap, 0 ), 2 * MEMORY_PAGE_SIZE );

    if2_memory_map_romcs[1].offset = MEMORY_PAGE_SIZE;
    if2_memory_map_romcs[1].page_num = 0;
    if2_memory_map_romcs[1].page =
      if2_memory_map_romcs[0].page + MEMORY_PAGE_SIZE;
  }

  ui_menu_activate( UI_MENU_ITEM_MEDIA_CARTRIDGE_IF2_EJECT, 1 );

  machine_current->memory_map();
}
