soup_message_body_get_chunk (SoupMessageBody *body, goffset offset)
{
	SoupMessageBodyPrivate *priv = (SoupMessageBodyPrivate *)body;
	GSList *iter;
	SoupBuffer *chunk = NULL;

	offset -= priv->base_offset;
	for (iter = priv->chunks; iter; iter = iter->next) {
		chunk = iter->data;

		if (offset < chunk->length || offset == 0)
			break;

		offset -= chunk->length;
	}

	if (!iter)
		return NULL;

	if (offset == 0)
		return soup_buffer_copy (chunk);
	else {
		return soup_buffer_new_subbuffer (chunk, offset,
						  chunk->length - offset);
	}
}
