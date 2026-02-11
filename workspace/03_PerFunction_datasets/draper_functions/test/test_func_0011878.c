about_window(void)
{
    gchar *path = gmpc_get_full_glade_path("aboutdialog.ui");
    GtkBuilder *xml = gtk_builder_new();
    GtkWidget *dialog = NULL;
    gtk_builder_add_from_file(xml, path, NULL);
    dialog = (GtkWidget *) gtk_builder_get_object(xml, "aboutdialog");

    gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(playlist3_get_window()));
    gtk_window_set_position(GTK_WINDOW(dialog), GTK_WIN_POS_CENTER_ON_PARENT);
    g_free(path);

    if (strlen(revision))
    {
        path = g_strdup_printf("%s\nRevision: %s", VERSION, revision);
    } else
    {
        path = g_strdup_printf("%s\n%s\n", VERSION, GMPC_TAGLINE);
    }
    gtk_about_dialog_set_copyright(GTK_ABOUT_DIALOG(dialog), GMPC_COPYRIGHT);
    gtk_about_dialog_set_program_name(GTK_ABOUT_DIALOG(dialog), _("Gnome Music Player Client"));
    gtk_about_dialog_set_website(GTK_ABOUT_DIALOG(dialog), GMPC_WEBSITE);
    gtk_about_dialog_set_version(GTK_ABOUT_DIALOG(dialog), path);

    g_free(path);
    gtk_widget_show(dialog);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    g_object_unref(xml);
}
