gwy_graph_window_destroy(GtkObject *object)
{
    GwyGraphWindow *graph_window = GWY_GRAPH_WINDOW(object);

    if (graph_window->data) {
        GwyGraphData *graph_data = GWY_GRAPH_DATA(graph_window->data);
        GwyGraphModel *gmodel = gwy_graph_data_get_model(graph_data);
        if (gmodel)
            g_signal_handlers_disconnect_by_func(gmodel,
                                                 graph_title_changed,
                                                 graph_window);
        graph_window->data = NULL;
    }

    GTK_OBJECT_CLASS(gwy_graph_window_parent_class)->destroy(object);
}
