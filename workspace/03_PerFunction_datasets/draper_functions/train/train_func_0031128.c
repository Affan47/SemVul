on_app_safe_focus_out_event            (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
    if (!fpm_window_check() && ini->tr_auto_hide && !state->minimized) {
	g_timeout_add_seconds(ini->tr_auto_hide_minutes*60, (GSourceFunc) fpm_auto_hide, gui->main_window);
}

  return FALSE;
}
