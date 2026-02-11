screen_on_event (GdkXEvent *xevent,
		 GdkEvent *event,
		 gpointer data)
{
#ifdef HAVE_RANDR
    GnomeRRScreen *screen = data;
    XEvent *e = xevent;
    int event_num;

    if (!e)
	return GDK_FILTER_CONTINUE;

    event_num = e->type - screen->randr_event_base;

    if (event_num == RRScreenChangeNotify) {


        screen_update (screen, TRUE, FALSE, NULL);
#if 0

	{
	    GtkWidget *dialog;
	    XRRScreenChangeNotifyEvent *rr_event;
	    static int dialog_num;

	    rr_event = (XRRScreenChangeNotifyEvent *) e;

	    dialog = gtk_message_dialog_new (NULL,
					     0,
					     GTK_MESSAGE_INFO,
					     GTK_BUTTONS_CLOSE,
					     "RRScreenChangeNotify timestamps (%d):\n"
					     "event change: %u\n"
					     "event config: %u\n"
					     "event serial: %lu\n"
					     "----------------------"
					     "screen change: %u\n"
					     "screen config: %u\n",
					     dialog_num++,
					     (guint32) rr_event->timestamp,
					     (guint32) rr_event->config_timestamp,
					     rr_event->serial,
					     (guint32) screen->info->resources->timestamp,
					     (guint32) screen->info->resources->configTimestamp);
	    g_signal_connect (dialog, "response",
			      G_CALLBACK (gtk_widget_destroy), NULL);
	    gtk_widget_show (dialog);
	}
#endif
    }
#if 0


    else if (event_num == RRNotify)
    {


	XRRNotifyEvent *event = (XRRNotifyEvent *)e;


	switch (event->subtype)
	{
	default:
	    break;
	}


	screen_update (screen, TRUE, FALSE, NULL);
    }
#endif

#endif


    return GDK_FILTER_CONTINUE;
}
