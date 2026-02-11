gst_flv_demux_video_negotiate (GstFlvDemux * demux, guint32 codec_tag)
{
  gboolean ret = FALSE;
  GstCaps *caps = NULL;
  gchar *codec_name = NULL;


  switch (codec_tag) {
    case 2:
      caps = gst_caps_new_simple ("video/x-flash-video", NULL);
      break;
    case 3:
      caps = gst_caps_new_simple ("video/x-flash-screen", NULL);
      break;
    case 4:
      caps = gst_caps_new_simple ("video/x-vp6-flash", NULL);
      break;
    case 5:
      caps = gst_caps_new_simple ("video/x-vp6-alpha", NULL);
      break;
    case 7:
      caps =
          gst_caps_new_simple ("video/x-h264", "stream-format", G_TYPE_STRING,
          "avc", NULL);
      break;
    default:
      GST_WARNING_OBJECT (demux, "unsupported video codec tag %u", codec_tag);
  }

  if (G_UNLIKELY (!caps)) {
    GST_WARNING_OBJECT (demux, "failed creating caps for video pad");
    goto beach;
  }

  gst_caps_set_simple (caps, "pixel-aspect-ratio", GST_TYPE_FRACTION,
      demux->par_x, demux->par_y, NULL);

  if (G_LIKELY (demux->w)) {
    gst_caps_set_simple (caps, "width", G_TYPE_INT, demux->w, NULL);
  }

  if (G_LIKELY (demux->h)) {
    gst_caps_set_simple (caps, "height", G_TYPE_INT, demux->h, NULL);
  }

  if (G_LIKELY (demux->framerate)) {
    gint num = 0, den = 0;

    gst_util_double_to_fraction (demux->framerate, &num, &den);
    GST_DEBUG_OBJECT (demux->video_pad,
        "fps to be used on caps %f (as a fraction = %d/%d)", demux->framerate,
        num, den);

    gst_caps_set_simple (caps, "framerate", GST_TYPE_FRACTION, num, den, NULL);
  }

  if (demux->video_codec_data) {
    gst_caps_set_simple (caps, "codec_data", GST_TYPE_BUFFER,
        demux->video_codec_data, NULL);
  }

  ret = gst_pad_set_caps (demux->video_pad, caps);

  if (G_LIKELY (ret)) {

    demux->video_codec_tag = codec_tag;

    codec_name = gst_pb_utils_get_codec_description (caps);

    if (codec_name) {
      if (demux->taglist == NULL)
        demux->taglist = gst_tag_list_new ();
      gst_tag_list_add (demux->taglist, GST_TAG_MERGE_REPLACE,
          GST_TAG_VIDEO_CODEC, codec_name, NULL);
      g_free (codec_name);
    }

    GST_DEBUG_OBJECT (demux->video_pad, "successfully negotiated caps %"
        GST_PTR_FORMAT, caps);
  } else {
    GST_WARNING_OBJECT (demux->video_pad, "failed negotiating caps %"
        GST_PTR_FORMAT, caps);
  }

  gst_caps_unref (caps);

beach:
  return ret;
}
