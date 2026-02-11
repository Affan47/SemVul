gwy_data_window_set_ul_corner_widget(GwyDataWindow *data_window,
                                     GtkWidget *corner)
{
    g_return_if_fail(GWY_IS_DATA_WINDOW(data_window));
    g_return_if_fail(!corner || GTK_IS_WIDGET(corner));

    if (corner == data_window->ul_corner)
        return;

    if (data_window->ul_corner)
        gtk_widget_unparent(data_window->ul_corner);

    if (corner)
        gtk_table_attach(GTK_TABLE(data_window->table), corner,
                         0, 1, 0, 1,
                         GTK_FILL, GTK_FILL, 0, 0);
    g_object_notify(G_OBJECT(data_window), "ul-corner");
}
