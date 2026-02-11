gdata_picasaweb_query_set_bounding_box (GDataPicasaWebQuery *self, gdouble north, gdouble east, gdouble south, gdouble west)
{
	g_return_if_fail (GDATA_IS_PICASAWEB_QUERY (self));
	g_return_if_fail (north >= -90.0 && north <= 90.0);
	g_return_if_fail (south >= -90.0 && south <= 90.0);
	g_return_if_fail (east >= -180.0 && east <= 180.0);
	g_return_if_fail (west >= -180.0 && west <= 180.0);

	self->priv->bounding_box.north = north;
	self->priv->bounding_box.east = east;
	self->priv->bounding_box.south = south;
	self->priv->bounding_box.west = west;


	gdata_query_set_etag (GDATA_QUERY (self), NULL);
}
