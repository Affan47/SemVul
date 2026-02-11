soup_body_input_stream_constructed (GObject *object)
{
	SoupBodyInputStream *bistream = SOUP_BODY_INPUT_STREAM (object);

	bistream->priv->base_stream = g_filter_input_stream_get_base_stream (G_FILTER_INPUT_STREAM (bistream));

	if (bistream->priv->encoding == SOUP_ENCODING_NONE ||
	    (bistream->priv->encoding == SOUP_ENCODING_CONTENT_LENGTH &&
	     bistream->priv->read_length == 0))
		bistream->priv->eof = TRUE;
}
