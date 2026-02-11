_gtk_window_get_group(GtkWindow * window)
{
    if (window && window->group)
        return window->group;
    else {
        static GtkWindowGroup *default_group = NULL;

        if (!default_group)
            default_group = gtk_window_group_new();

        return default_group;
    }
}
