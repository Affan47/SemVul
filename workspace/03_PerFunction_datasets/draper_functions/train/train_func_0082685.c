graph_title_changed(GwyGraphWindow *graphwindow)
{
    GwyGraphModel *gmodel;
    gchar *title;

    gmodel = gwy_graph_get_model(GWY_GRAPH(graphwindow->graph));
    g_object_get(gmodel, "title", &title, NULL);


    if (title)
        gtk_window_set_title(GTK_WINDOW(graphwindow), title);
    else
        gtk_window_set_title(GTK_WINDOW(graphwindow), _("Untitled"));

    g_free(title);
}
