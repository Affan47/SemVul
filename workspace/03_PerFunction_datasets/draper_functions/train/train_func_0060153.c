scld_from_snapshot( libspectrum_snap *snap )
{
  size_t i;
  int capabilities = machine_current->capabilities;

  if( capabilities & ( LIBSPECTRUM_MACHINE_CAPABILITY_TIMEX_MEMORY |
      LIBSPECTRUM_MACHINE_CAPABILITY_SE_MEMORY ) )
    scld_hsr_write( 0x00f4, libspectrum_snap_out_scld_hsr( snap ) );

  if( capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_TIMEX_VIDEO )
    scld_dec_write( 0x00ff, libspectrum_snap_out_scld_dec( snap ) );

  if( libspectrum_snap_dock_active( snap ) ) {

    dck_active = 1;

    for( i = 0; i < 8; i++ ) {

      if( libspectrum_snap_dock_cart( snap, i ) )
        scld_dock_exrom_from_snapshot( timex_dock, i,
          libspectrum_snap_dock_ram( snap, i ),
          libspectrum_snap_dock_cart( snap, i ) );

      if( libspectrum_snap_exrom_cart( snap, i ) )
        scld_dock_exrom_from_snapshot( timex_exrom, i,
          libspectrum_snap_exrom_ram( snap, i ),
          libspectrum_snap_exrom_cart( snap, i ) );

    }

    if( capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_TIMEX_DOCK )
      ui_menu_activate( UI_MENU_ITEM_MEDIA_CARTRIDGE_DOCK_EJECT, 1 );

    machine_current->memory_map();
  }

}
