mp3_tagger (GstElement *pipeline, GstPad *srcpad, GstTagList *tags)
{
	GstElement *mux = NULL;


	mux = gst_element_factory_make ("id3mux", NULL);
	if (mux == NULL)
		mux = gst_element_factory_make ("id3v2mux", NULL);

	if (mux == NULL)
		goto error;

	gst_bin_add (GST_BIN (pipeline), mux);
	if (!link_named_pad (srcpad, mux, "sink")) {
		rb_debug ("couldn't link decoded pad to id3 muxer");
		goto error;
	}

	gst_element_set_state (mux, GST_STATE_PAUSED);
	if (tags != NULL) {
		gst_tag_setter_merge_tags (GST_TAG_SETTER (mux), tags, GST_TAG_MERGE_REPLACE_ALL);
	}
	rb_debug ("id3 tagger created");
	return mux;

error:
	if (mux != NULL) {
		g_object_unref (mux);
	}
	return NULL;
}
