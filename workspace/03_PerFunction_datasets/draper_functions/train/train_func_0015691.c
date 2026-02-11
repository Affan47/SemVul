gvc_level_bar_size_allocate (GtkWidget     *widget,
                             GtkAllocation *allocation)
{
        GvcLevelBar *bar;

        g_return_if_fail (GVC_IS_LEVEL_BAR (widget));
        g_return_if_fail (allocation != NULL);

        bar = GVC_LEVEL_BAR (widget);


        GTK_WIDGET_CLASS (gvc_level_bar_parent_class)->size_allocate (widget, allocation);

        gtk_widget_set_allocation (widget, allocation);
        gtk_widget_get_allocation (widget, allocation);

        if (bar->priv->orientation == GTK_ORIENTATION_VERTICAL) {
                allocation->height = MIN (allocation->height, MIN_VERTICAL_BAR_HEIGHT);
                allocation->width = MAX (allocation->width, VERTICAL_BAR_WIDTH);
        } else {
                allocation->width = MIN (allocation->width, MIN_HORIZONTAL_BAR_WIDTH);
                allocation->height = MAX (allocation->height, HORIZONTAL_BAR_HEIGHT);
        }

        bar_calc_layout (bar);
}
