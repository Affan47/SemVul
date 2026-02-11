ensure_highlight_window(ParasiteWindow *parasite)
{
    GdkColor color;

    if (parasite->highlight_window != NULL)
        return;

    color.red = 0;
    color.green = 0;
    color.blue = 65535;

    parasite->highlight_window = gtk_window_new(GTK_WINDOW_POPUP);
    gtk_widget_modify_bg(parasite->highlight_window, GTK_STATE_NORMAL,
                         &color);

    g_signal_connect(G_OBJECT(parasite->highlight_window), "show",
                     G_CALLBACK(on_highlight_window_show), parasite);
}
