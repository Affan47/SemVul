noskin_post_init (gboolean unused)
{
  xine_cfg_entry_t entry;
  if (xine_config_lookup_entry (xine, "gui.window_size", &entry))
  {
    static const gdouble scale[] = { 50, 75, 100, 150, 200 };
    gtk_video_rescale ((GtkVideo *)gtv, scale[entry.num_value]);
  }
  if (xine_config_lookup_entry (xine, "gui.windowed_mode.magnify_lowres_video", &entry))
    gtk_video_set_auto_rescale ((GtkVideo *)gtv, entry.num_value);

  gxine_init_done ();
  return FALSE;
}
