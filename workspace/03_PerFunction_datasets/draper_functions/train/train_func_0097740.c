osm_gps_map_set_center (OsmGpsMap *map, float latitude, float longitude)
{
    int pixel_x, pixel_y;
    OsmGpsMapPrivate *priv;
    GtkAllocation allocation;

    g_return_if_fail (OSM_IS_GPS_MAP (map));

    priv = map->priv;
    gtk_widget_get_allocation(GTK_WIDGET(map), &allocation);
    g_object_set(G_OBJECT(map), "auto-center", FALSE, NULL);

    priv->center_rlat = deg2rad(latitude);
    priv->center_rlon = deg2rad(longitude);

    pixel_x = lon2pixel(priv->map_zoom, priv->center_rlon);
    pixel_y = lat2pixel(priv->map_zoom, priv->center_rlat);

    priv->map_x = pixel_x - allocation.width/2;
    priv->map_y = pixel_y - allocation.height/2;

    osm_gps_map_map_redraw_idle(map);

    g_signal_emit_by_name(map, "changed");
}
