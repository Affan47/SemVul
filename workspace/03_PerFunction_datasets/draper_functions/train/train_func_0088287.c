set_location (ChamplainLocation *location,
    gdouble latitude,
    gdouble longitude)
{
  g_return_if_fail (CHAMPLAIN_IS_COORDINATE (location));

  ChamplainCoordinatePrivate *priv = CHAMPLAIN_COORDINATE (location)->priv;

  priv->longitude = longitude;
  priv->latitude = latitude;

  g_object_notify (G_OBJECT (location), "latitude");
  g_object_notify (G_OBJECT (location), "longitude");
}
