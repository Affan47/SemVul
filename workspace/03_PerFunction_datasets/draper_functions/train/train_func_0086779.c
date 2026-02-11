create_default_world(void)
{
  const gchar *kilddir;
  gchar       *default_world_file;

  default_world = g_new0(World, 1);
  world_allocate_space_for_colors(default_world);


  default_world->charset = g_strdup("ISO-8859-1");
  default_world->charset_index = -1;

  default_world->terminalfont    = g_strdup(DEFAULT_TERMINAL_FONT);
  default_world->entryfont       = g_strdup(DEFAULT_TERMINAL_FONT);
  default_world->statusfont      = g_strdup("Sans 8");
  default_world->usebold         = TRUE;
  default_world->wrap            = TRUE;
  default_world->wrap_indent     = 0;
  default_world->wrap_column     = 40;
  default_world->use_wrap_column = FALSE;
  default_world->use_tooltips    = TRUE;

  memcpy(default_world->deffore,     &deffore,     sizeof(GdkColor));
  memcpy(default_world->defbold,     &defbold,     sizeof(GdkColor));
  memcpy(default_world->defback,     &defback,     sizeof(GdkColor));
  memcpy(default_world->defboldback, &defboldback, sizeof(GdkColor));
  memcpy(default_world->ansicolors,  &defansi,     16*sizeof(GdkColor));
  default_world->name_display_style   = NAME_DISPLAY_WORLD;
  default_world->name_display_pattern = g_strdup("%Kw [%Kc]");

  default_world->scrollOutput        = FALSE;
  default_world->buffer_lines        = 2000;

  default_world->repeat_commands     = FALSE;
  default_world->cmd_echo            = TRUE;
  default_world->never_hide_input    = FALSE;
  default_world->store_commands      = TRUE;
  default_world->commands_to_save    = 50;
  default_world->input_n_lines       = 1;
  default_world->input_n_lines_saved = 2;
  default_world->spell               = 1;
  default_world->autocompletion      = TRUE;
  default_world->autocompl_minprefix = 3;
  strcpy(default_world->command_separator, "%;");

  default_world->confirm_delete = TRUE;

  default_world->flood_prevention         = 1;
  default_world->max_equal_commands       = 20;
  default_world->flood_prevention_command = g_strdup("look");

  default_world->log_timeformat = g_strdup(DEFAULT_LOGTIME_FORMAT);
  default_world->log_add_time   = TRUE;
  default_world->log_autostart  = FALSE;

  default_world->keep_alive = FALSE;


  kilddir = get_kildclient_directory_path();
  default_world_file = g_build_filename(kilddir, "defworld.cfg", NULL);
  if (!load_world_from_file(default_world_file,
                            default_world,
                            FALSE,
                            NULL)) {
    default_world->file = default_world_file;
  } else {
    g_free(default_world_file);
  }
}
