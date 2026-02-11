libgnac_gst_newpad_cb(GstElement *decodebin,
                      GstPad     *pad,
                      gpointer    data)
{
  LibgnacMediaItem *item = (LibgnacMediaItem *) data;
	GstCaps *caps = gst_pad_get_caps(pad);

	if (gst_caps_is_empty(caps) || gst_caps_is_any(caps)) {
    libgnac_debug("Got a bad caps: %s", gst_caps_to_string(caps));
    gst_caps_unref(caps);
    return;
	}

	GstStructure *structure = gst_caps_get_structure(caps, 0);
	const gchar *mimetype = gst_structure_get_name(structure);

	if (g_str_has_prefix(mimetype, "audio/")) {
	  if (!libgnac_gstu_get_compatible_pad(item->audio_encoder, pad,
        caps, "audio"))
    {
      return;
    }
  } else if (g_str_has_prefix(mimetype, "video/")
      && item->video_channel != -1)
  {
	  if (!libgnac_gstu_get_compatible_pad(item->video_encoder, pad,
        caps, "video"))
    {
      return;
    }
	} else {
    libgnac_debug("Unhandled mime-type: %s", mimetype);
	}

	gst_caps_unref(caps);
}
