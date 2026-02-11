entangle_overlay_box_size_allocate(GtkWidget *widget,
                                   GtkAllocation *allocation)
{
    EntangleOverlayBox *box;
    EntangleOverlayBoxPrivate *priv;
    GtkAllocation under;
    GtkAllocation over;

    gtk_widget_set_allocation(widget, allocation);

    box = ENTANGLE_OVERLAY_BOX(widget);
    priv = box->priv;

    entangle_overlay_box_get_under_geometry(box, &under.x, &under.y, &under.width,
                                            &under.height);
    entangle_overlay_box_get_over_geometry(box, &over.x, &over.y, &over.width, &over.height);

    if (gtk_widget_get_realized(widget)) {
        gdk_window_move_resize(gtk_widget_get_window(widget),
                               allocation->x, allocation->y,
                               allocation->width, allocation->height);
        gdk_window_move_resize(priv->underWin, under.x, under.y, under.width,
                               under.height);
        gdk_window_move_resize(priv->overWin, over.x, over.y, over.width,
                               over.height);
    }

    under.x = 0;
    under.y = 0;
    gtk_widget_size_allocate(priv->under, &under);
    over.x = 0;
    over.y = 0;
    gtk_widget_size_allocate(priv->over, &over);
}
