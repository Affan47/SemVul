_gdata_media_group_add_content (GDataMediaGroup *self, GDataMediaContent *content)
{
	g_return_if_fail (GDATA_IS_MEDIA_GROUP (self));
	g_return_if_fail (GDATA_IS_MEDIA_CONTENT (content));
	self->priv->contents = g_list_prepend (self->priv->contents, g_object_ref (content));
}
