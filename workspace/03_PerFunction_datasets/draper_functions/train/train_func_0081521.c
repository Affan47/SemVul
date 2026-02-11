x_window_open_page (GSCHEM_TOPLEVEL *w_current, const gchar *filename)
{
  TOPLEVEL *toplevel = w_current->toplevel;
  PAGE *old_current, *page;
  gchar *fn;

  g_return_val_if_fail (toplevel != NULL, NULL);


  if (filename == NULL) {
    gchar *cwd, *tmp;
    cwd = g_get_current_dir ();
    tmp = g_strdup_printf ("%s_%d.sch",
                           toplevel->untitled_name,
                           ++w_current->num_untitled);
    fn = g_build_filename (cwd, tmp, NULL);
    g_free(cwd);
    g_free(tmp);
  } else {
    fn = g_strdup (filename);
  }


  page = s_page_search (toplevel, fn);
  if ( page != NULL ) {
    g_free(fn);
    return page;
  }

  old_current = toplevel->page_current;
  page = s_page_new (toplevel, fn);
  s_page_goto (toplevel, page);


  if (filename != NULL) {
    GError *err = NULL;
    if (!quiet_mode)
      s_log_message (_("Loading schematic [%s]\n"), fn);

    if (!f_open (toplevel, page, (gchar *) fn, &err)) {
      GtkWidget *dialog;

      g_warning ("%s\n", err->message);
      dialog = gtk_message_dialog_new_with_markup
        (GTK_WINDOW (w_current->main_window),
         GTK_DIALOG_DESTROY_WITH_PARENT,
         GTK_MESSAGE_ERROR,
         GTK_BUTTONS_CLOSE,
         _("<b>An error occurred while loading the requested file.</b>\n\nLoading from '%s' failed: %s. The gschem log may contain more information."),
         fn, err->message);
      gtk_window_set_title (GTK_WINDOW (dialog), _("Failed to load file"));
      gtk_dialog_run (GTK_DIALOG (dialog));
      gtk_widget_destroy (dialog);
      g_error_free (err);
    } else {
      gtk_recent_manager_add_item (recent_manager, g_filename_to_uri(fn, NULL, NULL));
    }
  } else {
    if (!quiet_mode)
      s_log_message (_("New file [%s]\n"),
                     toplevel->page_current->page_filename);

    g_run_hook_page (w_current, "%new-page-hook", toplevel->page_current);
  }

  a_zoom_extents (w_current,
                  s_page_objects (toplevel->page_current),
                  A_PAN_DONT_REDRAW);

  o_undo_savestate (w_current, UNDO_ALL);

  if ( old_current != NULL )
    s_page_goto (toplevel, old_current);


  x_pagesel_update (w_current);

  g_free (fn);

  return page;
}
