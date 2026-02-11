tree_view_column_set_default_width (GtkTreeView *view,
                                         GtkTreeViewColumn *column,
                                         const gchar *sizing_text)
{
    PangoLayout* layout;
    int default_width, title_width;
    const gchar *column_title;


    column_title = gtk_tree_view_column_get_title (column);
    layout = gtk_widget_create_pango_layout (GTK_WIDGET(view), column_title);
    pango_layout_get_pixel_size(layout, &title_width, NULL);
    g_object_unref(layout);
    layout = gtk_widget_create_pango_layout (GTK_WIDGET(view), sizing_text);
    pango_layout_get_pixel_size(layout, &default_width, NULL);
    g_object_unref(layout);
    default_width = MAX(default_width, title_width);
    if (default_width)
    {
        default_width += 10;
        g_object_set(G_OBJECT(column),
                     "sizing",      GTK_TREE_VIEW_COLUMN_FIXED,
                     "fixed-width", default_width,
                     NULL);
    }
}
