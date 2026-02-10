pad_added_cb (GstElement * element,
              GstPad * pad,
              GstElement *convert)
{

	GstPad *conv_pad;

	conv_pad = gst_element_get_static_pad (convert, "sink");
	g_assert (conv_pad != NULL);

	if (pads_compatible (pad, conv_pad)) {
		g_assert (!GST_PAD_IS_LINKED
			  (gst_element_get_static_pad
			   (convert, "sink")));

		gst_pad_link (pad, conv_pad);
	} else {
		g_warning ("Could not link GStreamer pipeline.");
	}
}
