osm_gps_map_get_bbox (OsmGpsMap *map, OsmGpsMapPoint *pt1, OsmGpsMapPoint *pt2)
{
    GtkAllocation allocation;
    OsmGpsMapPrivate *priv = map->priv;

    if (pt1 && pt2) {
        gtk_widget_get_allocation(GTK_WIDGET(map), &allocation);
        pt1->rlat = pixel2lat(priv->map_zoom, priv->map_y);
        pt1->rlon = pixel2lon(priv->map_zoom, priv->map_x);
        pt2->rlat = pixel2lat(priv->map_zoom, priv->map_y + allocation.height);
        pt2->rlon = pixel2lon(priv->map_zoom, priv->map_x + allocation.width);
    }
}
