osm_gps_map_track_add_point (OsmGpsMapTrack *track, const OsmGpsMapPoint *point)
{
    g_return_if_fail (OSM_IS_GPS_MAP_TRACK (track));
    OsmGpsMapTrackPrivate *priv = track->priv;

    OsmGpsMapPoint *p = g_boxed_copy (OSM_TYPE_GPS_MAP_POINT, point);
    priv->track = g_slist_append (priv->track, p);
    g_signal_emit (track, signals[POINT_ADDED], 0, p);
}
