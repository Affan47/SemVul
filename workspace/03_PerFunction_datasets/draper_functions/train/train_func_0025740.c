hide_axis_settings_callback(GtkWidget *widget, gpointer func_data)
{
  int i;

    if (gtk_toggle_action_get_active(GTK_TOGGLE_ACTION(widget))) {
        for (i=0;i<MAXNUMTABS;i++) if (logbox[i] != NULL) gtk_widget_hide(logbox[i]);
	HideLog = TRUE;
    } else {
        for (i=0;i<MAXNUMTABS;i++) if (logbox[i] != NULL) gtk_widget_show(logbox[i]);
	HideLog = FALSE;
    }
  return NULL;
}
