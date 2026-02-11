gtk_bar_new(GtkOrientation orient, gint spacing,
    gint child_height, gint child_width)
{
    GtkBar *bar;

    bar = g_object_new (GTK_TYPE_BAR, NULL);
    GTK_BOX (bar)->spacing = spacing;
    bar->orient = orient;
    bar->child_width = MAX(1, child_width);
    bar->child_height = MAX(1, child_height);
    bar->dimension = 1;
    return (GtkWidget *)bar;
}
