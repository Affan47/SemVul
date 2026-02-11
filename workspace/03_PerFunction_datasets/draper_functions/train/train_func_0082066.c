lcrt_options_on_session_options_activate(GtkMenuItem *menuitem, gpointer user_data)
{
    struct lcrt_options *loptions = (struct lcrt_options *)user_data;
    struct lcrt_settings *lsettings = loptions->parent->parent->w_settings;
    int rv;

    if (gtk_notebook_get_n_pages(GTK_NOTEBOOK(lsettings->parent->w_notebook->notebook)) == 0)
        return;
#if 0
    lsettings->session = TRUE;
    gtk_notebook_set_current_page(GTK_NOTEBOOK(lsettings->notebook), 2);
    gtk_notebook_set_show_tabs(GTK_NOTEBOOK(lsettings->notebook), FALSE);
    gtk_widget_show(lsettings->dialog_settings);
#else
    lcrt_create_qconnect(loptions->parent->parent,
                         NULL,
                         LCRT_QCONNECT_SESSION_OPTION,
                         loptions->parent->parent->current_user->name,
                         NULL);

#endif
}
