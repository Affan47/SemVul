gtk_multiview_map(GtkWidget * widget)
{
    GtkMultiview *multiview;

    g_return_if_fail(widget != NULL);
    g_return_if_fail(GTK_IS_MULTIVIEW(widget));

    multiview = GTK_MULTIVIEW(widget);
    gtk_widget_set_mapped(widget, TRUE);

    if (multiview->current && gtk_widget_get_visible(multiview->current) && !gtk_widget_get_mapped(multiview->current)) {
        gtk_widget_map(GTK_WIDGET(multiview->current));
    }
}
