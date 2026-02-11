update_subtitles_menu (void)
{
  if (ui)
    update_subtitles_menu_internal (ui_get_action_group (ui));
}
