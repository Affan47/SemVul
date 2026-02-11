status_update(struct w *widgets)
{
    char *pid;
    gchar *info1, *utf8=NULL;

    GdkColor color;


    pid = get_process_pid("rsync");
    if( strcmp(pid, "0") == 0 )
    {
        client_active = 0;
	info1 = g_strdup_printf(_("Status: Backup is not running."));
    }
    else
    {
        client_active = 1;
        info1 = g_strdup_printf(_("Status: Backup is running."));
    }
    free(pid);


    utf8 = g_locale_to_utf8(info1, strlen(info1), NULL, NULL, NULL);
    gtk_label_set_text(GTK_LABEL(widgets->status_label), utf8);
    if( utf8!=NULL )
      g_free(utf8);

    g_free(info1);


    if( client_active )
    {

	gdk_color_parse("dark green", &color);
	gtk_widget_modify_fg(widgets->status_label, GTK_STATE_NORMAL, &color);
    }
    else
    {

	gdk_color_parse("red", &color);
	gtk_widget_modify_fg(widgets->status_label, GTK_STATE_NORMAL, &color);
    }

    return (TRUE);
}
