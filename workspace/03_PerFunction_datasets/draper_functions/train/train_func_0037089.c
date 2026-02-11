got_chunk_cb (SoupMessage *message, SoupBuffer *buffer, GDataDownloadStream *self)
{

	if (SOUP_STATUS_IS_SUCCESSFUL (message->status_code) == FALSE || buffer->length == 0)
		return;


	g_assert (self->priv->buffer != NULL);
	gdata_buffer_push_data (self->priv->buffer, (const guint8*) buffer->data, buffer->length);
}
