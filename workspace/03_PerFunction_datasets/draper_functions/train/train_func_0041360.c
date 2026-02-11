gnac_profiles_mgr_display_import_status(guint profiles_ok,
                                        guint profiles_error)
{
  gchar *oks = NULL;
  gchar *errors = NULL;

  if (profiles_error > 0) {
    errors = g_strdup_printf(ngettext("%d file failed to be imported",
        "%d files failed to be imported", profiles_error), profiles_error);
  }

  if (profiles_ok > 0) {
    oks = g_strdup_printf(ngettext("%d file successfully imported",
        "%d files successfully imported", profiles_ok), profiles_ok);
  }

  gdk_threads_enter();
    gnac_profiles_mgr_set_window_sensitive(TRUE);
    gnac_profiles_mgr_show_import_progressbar(FALSE);
    gnac_profiles_mgr_display_status_message(oks, errors);
  gdk_threads_leave();

  g_free(oks);
  g_free(errors);
}
