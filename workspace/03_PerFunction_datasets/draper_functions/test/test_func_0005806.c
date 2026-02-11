validate_src_pads (gpointer item, GValue *ret, gpointer user_data)
{
  GstPad *pad = item;
  GList *codecs = user_data;
  GstCaps *caps;
  GList *listitem = NULL;
  gboolean retval = FALSE;

  caps = gst_pad_get_caps_reffed (pad);

  if (gst_caps_is_empty (caps))
  {
    GST_WARNING_OBJECT (pad, "Caps on pad are empty");
    goto error;
  }

  for (listitem = codecs; listitem; listitem = g_list_next (listitem))
  {
    FsCodec *codec = listitem->data;
    GstCaps *tmpcaps = fs_codec_to_gst_caps (codec);

    if (gst_caps_can_intersect (tmpcaps, caps))
    {
      GST_LOG_OBJECT (pad, "Pad matches " FS_CODEC_FORMAT,
          FS_CODEC_ARGS (codec));
      retval = TRUE;
    }
    gst_caps_unref (tmpcaps);

    if (retval)
      break;
  }

 error:

  gst_object_unref (pad);
  gst_caps_unref (caps);
  if (!retval)
    g_value_set_boolean (ret, FALSE);
  return retval;
}
