activate_cb(SimoComboBox *cmb, gpointer data)
{
  World *world = ((WorldGUI *) data)->world;

  if (world) {
    const gchar *str;

    str = simo_combo_box_get_text(cmb);
    parse_commands(world, str, strlen(str));


    if (strcmp(str, "") != 0 && !world->noecho) {
      add_recent_command(world, str);
    }
  }
  if (world->noecho || !world->repeat_commands)
    simo_combo_box_set_text(cmb, "");
  else
    simo_combo_box_select_region(cmb, 0, -1);

  if (world->itime_reset_activate) {
    world->last_command_time = time(NULL);
  }
  world->cmd_position_changed = FALSE;
}
