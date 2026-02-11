get_latitude (ChamplainLocation *location)
{
  g_return_val_if_fail (CHAMPLAIN_IS_COORDINATE (location), 0.0);

  ChamplainCoordinatePrivate *priv = CHAMPLAIN_COORDINATE (location)->priv;

  return priv->latitude;
}
