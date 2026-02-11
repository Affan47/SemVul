_on_timeout (PhotoData *data)
{
  gboolean quit = TRUE;

  data->timeout_id = 0;
  if (data->idle_id > 0) {
    g_source_remove (data->idle_id);
    data->idle_id = 0;
  }

  if (data->force) {
    switch (webkit_web_view_get_load_status (data->webview)) {
      case WEBKIT_LOAD_FIRST_VISUALLY_NON_EMPTY_LAYOUT:
      case WEBKIT_LOAD_FINISHED:

        g_printerr (_("Timed out while loading '%s'. Outputting current view...\n"), data->uri);

        if (data->delay > 0) {
          quit = FALSE;
          data->delay_id = g_timeout_add_seconds (data->delay,
                                                  (GSourceFunc) _on_delay, data);
        } else
          _do_action (data);

        break;

      default:
        data->error = TRUE;

        g_printerr (_("Timed out while loading '%s'. Nothing to output...\n"), data->uri);
        break;
    }
  } else {
    data->error = TRUE;

    g_printerr (_("Timed out while loading '%s'.\n"), data->uri);
  }


  webkit_web_view_stop_loading (data->webview);

  if (quit)
    gtk_main_quit ();

  return FALSE;
}
