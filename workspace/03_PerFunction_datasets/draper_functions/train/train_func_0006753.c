on_toggle_toolbar( GtkMenuItem* item, MainWin* mw )
{
    pref.show_toolbar = !pref.show_toolbar;

    if (pref.show_toolbar)
        gtk_widget_show(gtk_widget_get_parent(mw->nav_bar));
    else
        gtk_widget_hide(gtk_widget_get_parent(mw->nav_bar));

    save_preferences();
}
