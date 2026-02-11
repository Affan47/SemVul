gwy_graph_window_measure_finished(GwyGraphWindow *graphwindow, gint response)
{
    GwyGraphArea *area;

    area = GWY_GRAPH_AREA(gwy_graph_get_area(GWY_GRAPH(graphwindow->graph)));

    if (response == GWY_GRAPH_WINDOW_MEASURE_RESPONSE_CLEAR) {
        GwyGraphStatusType status;
        status = gwy_graph_area_get_status(area);
        gwy_selection_clear(gwy_graph_area_get_selection(area, status));
        return;
    }

    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(graphwindow->button_measure_points), FALSE);
    gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(graphwindow->button_zoom_in), FALSE);
    gwy_graph_set_status(GWY_GRAPH(graphwindow->graph), GWY_GRAPH_STATUS_PLAIN);

    gtk_widget_queue_draw(graphwindow->graph);
    gtk_widget_hide(graphwindow->measure_dialog);
}
