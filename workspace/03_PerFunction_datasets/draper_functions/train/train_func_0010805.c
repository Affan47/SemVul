display_refresh_all(void)
{
  size_t i;

  display_redraw_all = 1;

  display_refresh_main_screen();

  for( i = 0; i < DISPLAY_SCREEN_HEIGHT; i++ )
    display_is_dirty[i] = display_all_dirty;

  memset( display_last_screen, 0xff,
          DISPLAY_SCREEN_WIDTH_COLS * DISPLAY_SCREEN_HEIGHT
          * sizeof(libspectrum_dword) );
}
