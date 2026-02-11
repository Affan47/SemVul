osm_gps_map_map_redraw (OsmGpsMap *map)
{
    cairo_t *cr;
    int w, h;
    OsmGpsMapPrivate *priv = map->priv;
    GtkWidget *widget = GTK_WIDGET(map);

    priv->idle_map_redraw = 0;


    if (!priv->pixmap)
        return FALSE;


    if (priv->layers) {
        GSList *list;
        for(list = priv->layers; list != NULL; list = list->next) {
            OsmGpsMapLayer *layer = list->data;
            if (osm_gps_map_layer_busy(layer))
                return FALSE;
        }
    }


    if (priv->is_dragging)
        return FALSE;


    cr = cairo_create (priv->pixmap);


    priv->drag_mouse_dx = 0;
    priv->drag_mouse_dy = 0;

    priv->redraw_cycle++;


    w = gtk_widget_get_allocated_width (widget);
    h = gtk_widget_get_allocated_width (widget);
    draw_white_rectangle(cr, 0, 0, w + EXTRA_BORDER * 2, h + EXTRA_BORDER * 2);

    osm_gps_map_fill_tiles_pixel(map, cr);

    osm_gps_map_print_tracks(map, cr);
    osm_gps_map_print_images(map, cr);


    if (priv->gps_track_used && priv->gps_point_enabled) {
        OsmGpsMapClass *klass = OSM_GPS_MAP_GET_CLASS(map);
        if (klass->draw_gps_point)
            klass->draw_gps_point (map, cr);
    }

    if (priv->layers) {
        GSList *list;
        for(list = priv->layers; list != NULL; list = list->next) {
            OsmGpsMapLayer *layer = list->data;
            osm_gps_map_layer_render (layer, map);
        }
    }

    osm_gps_map_purge_cache(map);
    gtk_widget_queue_draw (GTK_WIDGET (map));

    cairo_destroy (cr);

    return FALSE;
}
