gwy_graph_axis_rescaled(GwyAxis *axis, GwyGraph *graph)
{
    GwyGraphGridType grid_type;
    gdouble min, max;

    if (graph->graph_model == NULL)
        return;

    gwy_debug("%p: axis %p", graph, axis);

    gwy_axis_get_range(axis, &min, &max);
    if (axis == graph->axis[GTK_POS_BOTTOM])
        gwy_graph_area_set_x_range(graph->area, min, max);
    if (axis == graph->axis[GTK_POS_LEFT])
        gwy_graph_area_set_y_range(graph->area, min, max);

    g_object_get(graph->graph_model, "grid-type", &grid_type, NULL);
    if (grid_type == GWY_GRAPH_GRID_AUTO) {
        const gdouble *ticks;
        guint nticks;

        ticks = gwy_axis_get_major_ticks(axis, &nticks);
        if (axis == graph->axis[GTK_POS_BOTTOM])
            gwy_graph_area_set_x_grid_data(graph->area, nticks, ticks);
        if (axis == graph->axis[GTK_POS_LEFT])
            gwy_graph_area_set_y_grid_data(graph->area, nticks, ticks);
    }
}
