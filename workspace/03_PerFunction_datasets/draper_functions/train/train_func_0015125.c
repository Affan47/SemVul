_cancel_sync(GtkWidget * widget, gpointer data)
{
    SyncDialog *sd = (SyncDialog *) data;

    if (session) {
	soup_session_abort(session);
    }

    sd->flag_cancel = TRUE;
    g_main_quit(loop);

    gtk_widget_set_sensitive(widget, FALSE);

    return FALSE;
}
