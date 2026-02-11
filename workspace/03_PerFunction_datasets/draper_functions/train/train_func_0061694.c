gdata_youtube_video_look_up_content (GDataYouTubeVideo *self, const gchar *type)
{
	g_return_val_if_fail (GDATA_IS_YOUTUBE_VIDEO (self), NULL);
	g_return_val_if_fail (type != NULL, NULL);

	return GDATA_YOUTUBE_CONTENT (gdata_media_group_look_up_content (self->priv->media_group, type));
}
