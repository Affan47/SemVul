brasero_metadata_process_pending_messages (BraseroMetadata *self)
{
	GstBus *bus;
	GstMessage *msg;
	BraseroMetadataPrivate *priv;

	priv = BRASERO_METADATA_PRIVATE (self);

	bus = gst_pipeline_get_bus (GST_PIPELINE (priv->pipeline));
	while ((msg = gst_bus_pop (bus))) {
		GstTagList *tags = NULL;

		if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_TAG) {
			gst_message_parse_tag (msg, &tags);
			gst_tag_list_foreach (tags, (GstTagForeachFunc) foreach_tag, self);
			gst_tag_list_free (tags);
		}
		else if (GST_MESSAGE_TYPE (msg) == GST_MESSAGE_ELEMENT)
			brasero_metadata_process_element_messages (self, msg);

		gst_message_unref (msg);
	}

	g_object_unref (bus);
}
