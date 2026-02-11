ui_menu_disk_update( void )
{
  int plus3, beta, plusd, opus, disciple;
  int capabilities;

  capabilities = machine_current->capabilities;


  plus3 = capabilities & LIBSPECTRUM_MACHINE_CAPABILITY_PLUS3_DISK;
  beta = beta_available;
  opus = opus_available;
  plusd = plusd_available;
  disciple = disciple_available;

  if( plus3 || beta || opus || plusd || disciple ) {
    ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK, 1 );
    ui_statusbar_update( UI_STATUSBAR_ITEM_DISK, UI_STATUSBAR_STATE_INACTIVE );
  } else {
    ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK, 0 );
    ui_statusbar_update( UI_STATUSBAR_ITEM_DISK,
                         UI_STATUSBAR_STATE_NOT_AVAILABLE );
  }

  ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK_PLUS3, plus3 );
  ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK_BETA, beta );
  ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK_OPUS, opus );
  ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK_PLUSD, plusd );
  ui_menu_activate( UI_MENU_ITEM_MEDIA_DISK_DISCIPLE, disciple );
}
