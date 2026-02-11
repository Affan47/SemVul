quit(gboolean force)
{
	gboolean confirm;


	if (quitting)
		return;

    gui_prop_get_boolean_val(PROP_CONFIRM_QUIT, &confirm);
    if (force || !confirm) {
		quitting = TRUE;
		crash_ctl(CRASH_FLAG_CLEAR, CRASH_F_RESTART);
       	guc_gtk_gnutella_exit(0);
	} else {
        gtk_widget_show(gui_dlg_quit());
    	gdk_window_raise(gui_dlg_quit()->window);
	}
}
