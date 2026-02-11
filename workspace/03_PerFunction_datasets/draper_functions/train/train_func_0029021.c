ui_exit()
{

#if defined UNDER_CE && defined SMALL_SCREEN

  set_video_mode(320, 240, SDL_SWSURFACE | SDL_ANYFORMAT);
#endif

  free_mapcanvas_and_overview();

  free_auxiliary_tech_icons();
  free_intro_radar_sprites();

  diplomacy_dialog_done();
  intel_dialog_done();

  callback_list_destroy(callbacks);

  unload_cursors();

  FC_FREE(button_behavior.event);

  meswin_dialog_popdown();

  del_main_list();

  free_font_system();
  theme_free(theme);

  quit_sdl();
}
