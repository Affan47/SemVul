plusd_disk_insert( plusd_drive_number which, const char *filename,
		   int autoload )
{
  int error;
  wd_fdc_drive *d;
  const fdd_params_t *dt;

  if( which >= PLUSD_NUM_DRIVES ) {
    ui_error( UI_ERROR_ERROR, "plusd_disk_insert: unknown drive %d",
	      which );
    fuse_abort();
  }

  d = &plusd_drives[ which ];


  if( d->fdd.loaded ) {

    if( plusd_disk_eject( which ) ) return 0;
  }

  if( filename ) {
    error = disk_open( &d->disk, filename, 0, DISK_TRY_MERGE( d->fdd.fdd_heads ) );
    if( error != DISK_OK ) {
      ui_error( UI_ERROR_ERROR, "Failed to open disk image: %s",
				disk_strerror( error ) );
      return 1;
    }
  } else {
    switch( which ) {
    case 0:
      dt = &fdd_params[ option_enumerate_diskoptions_drive_plusd1_type() + 1 ];
      break;
    case 1:
    default:
      dt = &fdd_params[ option_enumerate_diskoptions_drive_plusd2_type() ];
      break;
    }
    error = disk_new( &d->disk, dt->heads, dt->cylinders, DISK_DENS_AUTO, DISK_UDI );
    if( error != DISK_OK ) {
      ui_error( UI_ERROR_ERROR, "Failed to create disk image: %s",
				disk_strerror( error ) );
      return 1;
    }
  }

  fdd_load( &d->fdd, &d->disk, 0 );


  switch( which ) {
  case PLUSD_DRIVE_1:
    ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK_PLUSD_1_EJECT, 1 );
    ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK_PLUSD_1_FLIP_SET,
		      !plusd_drives[ PLUSD_DRIVE_1 ].fdd.upsidedown );
    ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK_PLUSD_1_WP_SET,
		      !plusd_drives[ PLUSD_DRIVE_1 ].fdd.wrprot );
    break;
  case PLUSD_DRIVE_2:
    ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK_PLUSD_2_EJECT, 1 );
    ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK_PLUSD_2_FLIP_SET,
		      !plusd_drives[ PLUSD_DRIVE_2 ].fdd.upsidedown );
    ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK_PLUSD_2_WP_SET,
		      !plusd_drives[ PLUSD_DRIVE_2 ].fdd.wrprot );
    break;
  }

  if( filename && autoload ) {

  }

  return 0;
}
