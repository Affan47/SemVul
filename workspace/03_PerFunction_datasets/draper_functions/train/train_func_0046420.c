osm_gps_map_set_zoom (OsmGpsMap *map, int zoom)
{
    int width_center, height_center;
    OsmGpsMapPrivate *priv;
    GtkAllocation allocation;

    g_return_val_if_fail (OSM_IS_GPS_MAP (map), 0);
    priv = map->priv;

    if (zoom != priv->map_zoom)
    {
        gtk_widget_get_allocation(GTK_WIDGET(map), &allocation);
        width_center  = allocation.width / 2;
        height_center = allocation.height / 2;


        priv->map_zoom = CLAMP(zoom, priv->min_zoom, priv->max_zoom);
        priv->map_x = lon2pixel(priv->map_zoom, priv->center_rlon) - width_center;
        priv->map_y = lat2pixel(priv->map_zoom, priv->center_rlat) - height_center;

        osm_gps_map_map_redraw_idle(map);

        g_signal_emit_by_name(map, "changed");
        g_object_notify(G_OBJECT(map), "zoom");
    }
    return priv->map_zoom;
}
