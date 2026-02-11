gwy_app_graph_popup_menu_popup_mouse(GtkWidget *menu,
                                     GdkEventButton *event,
                                     GwyGraph *graph)
{
    if (event->button != 3)
        return FALSE;

    if (GWY_IS_GRAPH_AREA(graph)) {
        graph = GWY_GRAPH(gtk_widget_get_ancestor(GTK_WIDGET(graph),
                                                  GWY_TYPE_GRAPH));
        if (!graph)
            return FALSE;
    }
    gwy_app_data_browser_select_graph(graph);
    gtk_menu_popup(GTK_MENU(menu), NULL, NULL, NULL, NULL,
                   event->button, event->time);

    return TRUE;
}
