um_crop_area_button_press_event (GtkWidget      *widget,
                                 GdkEventButton *event)
{
        UmCropArea *area = UM_CROP_AREA (widget);
        GdkRectangle crop;

        if (area->priv->browse_pixbuf == NULL)
                return FALSE;

        crop_to_widget (area, &crop);

        area->priv->last_press_x = (event->x - area->priv->image.x) / area->priv->scale;
        area->priv->last_press_y = (event->y - area->priv->image.y) / area->priv->scale;
        area->priv->active_region = find_location (&crop, event->x, event->y);

        gtk_widget_queue_draw_area (widget,
                                    crop.x - 1, crop.y - 1,
                                    crop.width + 2, crop.height + 2);

        return FALSE;
}
