gwy_graph_finalize(GObject *object)
{
    GwyGraph *graph = GWY_GRAPH(object);

    gwy_signal_handler_disconnect(graph->zoom_selection,
                                  graph->zoom_finished_id);
    gwy_signal_handler_disconnect(graph->graph_model, graph->model_notify_id);
    gwy_signal_handler_disconnect(graph->graph_model,
                                  graph->curve_data_changed_id);
    gwy_object_unref(graph->graph_model);
    gwy_object_unref(graph->zoom_selection);

    G_OBJECT_CLASS(gwy_graph_parent_class)->finalize(object);
}
