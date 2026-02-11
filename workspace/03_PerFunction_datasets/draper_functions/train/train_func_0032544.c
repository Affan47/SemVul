create_popupwin(DataTree* data)
{
	GtkWidget *MainFrame;
	GtkWidget *hbox = gtk_hbox_new(0,FALSE);

 	popupshow = TRUE;

	MainFrame = gtk_window_new (GTK_WINDOW_POPUP);


        gtk_window_set_position(GTK_WINDOW (MainFrame), GTK_WIN_POS_MOUSE);


        gtk_widget_add_events(MainFrame,
                              GDK_BUTTON_PRESS_MASK|
                              GDK_BUTTON_RELEASE_MASK|
                              GDK_KEY_PRESS_MASK);

        g_signal_connect(G_OBJECT(MainFrame),"button_release_event",
                G_CALLBACK(destroy_popup),NULL);
        g_signal_connect(G_OBJECT(MainFrame),"key_press_event",
                G_CALLBACK(gtk_widget_destroy),NULL);
        gtk_widget_realize(MainFrame);

        gtk_widget_show(hbox);
        gtk_container_add (GTK_CONTAINER (MainFrame), hbox);
	create_local_frame_popup(hbox,data);
	create_remote_frame_popup(hbox,data);
        gtk_widget_show_all(MainFrame);


        while(gtk_events_pending())
                gtk_main_iteration();


}
