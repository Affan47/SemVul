brasero_transcode_new_decoded_pad_cb (GstElement *decode,
				      GstPad *pad,
				      BraseroTranscode *transcode)
{
	GstCaps *caps;
	GstStructure *structure;
	BraseroTranscodePrivate *priv;

	priv = BRASERO_TRANSCODE_PRIVATE (transcode);

	BRASERO_JOB_LOG (transcode, "New pad");


	caps = gst_pad_query_caps (pad, NULL);
	if (!caps)
		return;

	structure = gst_caps_get_structure (caps, 0);
	if (structure) {
		if (g_strrstr (gst_structure_get_name (structure), "audio")) {
			GstPad *sink;
			GstElement *queue;
			GstPadLinkReturn res;


			brasero_transcode_send_volume_event (transcode);


			queue = gst_element_factory_make ("queue", NULL);
			gst_bin_add (GST_BIN (priv->pipeline), queue);
			if (!gst_element_link (queue, priv->link)) {
				brasero_transcode_error_on_pad_linking (transcode, "Sent by brasero_transcode_new_decoded_pad_cb");
				goto end;
			}

			sink = gst_element_get_static_pad (queue, "sink");
			if (GST_PAD_IS_LINKED (sink)) {
				brasero_transcode_error_on_pad_linking (transcode, "Sent by brasero_transcode_new_decoded_pad_cb");
				goto end;
			}

			res = gst_pad_link (pad, sink);
			if (res == GST_PAD_LINK_OK)
				gst_element_set_state (queue, GST_STATE_PLAYING);
			else
				brasero_transcode_error_on_pad_linking (transcode, "Sent by brasero_transcode_new_decoded_pad_cb");

			gst_object_unref (sink);
		}

		else if (g_strrstr (gst_structure_get_name (structure), "video")) {
			GstPad *sink;
			GstElement *fakesink;
			GstPadLinkReturn res;

			BRASERO_JOB_LOG (transcode, "Adding a fakesink for video stream");

			fakesink = gst_element_factory_make ("fakesink", NULL);
			if (!fakesink) {
				brasero_transcode_error_on_pad_linking (transcode, "Sent by brasero_transcode_new_decoded_pad_cb");
				goto end;
			}

			sink = gst_element_get_static_pad (fakesink, "sink");
			if (!sink) {
				brasero_transcode_error_on_pad_linking (transcode, "Sent by brasero_transcode_new_decoded_pad_cb");
				gst_object_unref (fakesink);
				goto end;
			}

			gst_bin_add (GST_BIN (priv->pipeline), fakesink);
			res = gst_pad_link (pad, sink);

			if (res == GST_PAD_LINK_OK)
				gst_element_set_state (fakesink, GST_STATE_PLAYING);
			else
				brasero_transcode_error_on_pad_linking (transcode, "Sent by brasero_transcode_new_decoded_pad_cb");

			gst_object_unref (sink);
		}
	}

end:
	gst_caps_unref (caps);
}
