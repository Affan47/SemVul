themespec_reread(const char *new_theme_name)
{
  struct tile *center_tile;
  enum client_states state = client_state();
  const char *name = new_theme_name ? new_theme_name : theme->name;
  char theme_name[strlen(name) + 1], old_name[strlen(theme->name) + 1];


  sz_strlcpy(theme_name, name);
  sz_strlcpy(old_name, theme->name);

  log_normal(_("Loading theme \"%s\"."), theme_name);


  center_tile = get_center_tile_mapcanvas();


  theme_free_sprites(theme);
  theme_free_toplevel(theme);


  if (!(theme = theme_read_toplevel(theme_name))) {
    if (!(theme = theme_read_toplevel(old_name))) {

      fc_assert_exit_msg(NULL != theme,
                         "Failed to re-read the currently loaded theme.");
    }
  }

  theme_load_sprites(theme);


  if (state < C_S_RUNNING) {

    return;
  }


  popdown_all_game_dialogs();
  generate_citydlg_dimensions();

  can_slide = FALSE;
  center_tile_mapcanvas(center_tile);


  update_map_canvas_visible();
  can_slide = TRUE;
}
