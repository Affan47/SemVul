gst_videomixer2_pad_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstVideoMixer2Pad *pad = GST_VIDEO_MIXER2_PAD (object);
  GstVideoMixer2 *mix = GST_VIDEO_MIXER2 (gst_pad_get_parent (GST_PAD (pad)));

  switch (prop_id) {
    case PROP_PAD_ZORDER:
      GST_VIDEO_MIXER2_LOCK (mix);
      pad->zorder = g_value_get_uint (value);

      mix->sinkpads = g_slist_sort (mix->sinkpads,
          (GCompareFunc) pad_zorder_compare);
      GST_VIDEO_MIXER2_UNLOCK (mix);
      break;
    case PROP_PAD_XPOS:
      pad->xpos = g_value_get_int (value);
      break;
    case PROP_PAD_YPOS:
      pad->ypos = g_value_get_int (value);
      break;
    case PROP_PAD_ALPHA:
      pad->alpha = g_value_get_double (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }

  gst_object_unref (mix);
}
