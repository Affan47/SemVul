on_menu_projopen_activate (GtkWidget *widget, void *user) {

    gchar* filename = get_open_filename (TYPE_PROJECT);
    if (!filename) return;

    if (project_open_existing (filename)) {
        statusbar_set_message (g_strdup_printf("Loading project %s", filename));
        projectgui_enable (gummi->project, gui->projectgui);
        projectgui_list_projfiles (gummi->project->projfile);
    }
    else {
        statusbar_set_message (g_strdup_printf("An error ocurred while "
                                               "loading project %s", filename));
    }
    g_free (filename);
}
