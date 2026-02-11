link_other_pads (const GValue *item, GValue *ret, gpointer user_data)
{
  GstPad *pad = g_value_get_object (item);
  struct link_data *data = user_data;
  GstCaps *caps;
  GstCaps *filter_caps = NULL;
  GList *listitem;
  GstElement *capsfilter;
  GstPad *otherpad;

  if (gst_pad_is_linked (pad))
  {
    return TRUE;
  }

  caps = gst_pad_query_caps (pad, NULL);

  if (gst_caps_is_empty (caps))
  {
    GST_WARNING_OBJECT (pad, "Caps on pad are empty");
    return TRUE;
  }

  for (listitem = data->all_codecs; listitem; listitem = g_list_next (listitem))
  {
    FsCodec *codec = listitem->data;

    filter_caps = fs_codec_to_gst_caps (codec);

    if (gst_caps_can_intersect (filter_caps, caps))
    {
      GST_LOG_OBJECT (pad, "Pad matches " FS_CODEC_FORMAT,
          FS_CODEC_ARGS (codec));
      break;
    }

    gst_caps_unref (filter_caps);
  }

  gst_caps_unref (caps);

  if (!listitem)
  {
    g_set_error (data->error, FS_ERROR, FS_ERROR_INTERNAL,
        "Could not find codec that matches the src pad");
    g_value_set_boolean (ret, FALSE);
    return FALSE;
  }

  capsfilter = gst_element_factory_make ("capsfilter", NULL);
  g_object_set (capsfilter, "caps", filter_caps, NULL);

  if (!gst_bin_add (GST_BIN (data->session->priv->conference), capsfilter))
  {
    g_set_error (data->error, FS_ERROR, FS_ERROR_CONSTRUCTION,
        "Could not add send capsfilter to the conference");
    gst_object_unref (capsfilter);
    goto error;
  }

  data->session->priv->extra_send_capsfilters =
    g_list_append (data->session->priv->extra_send_capsfilters,
        capsfilter);

  otherpad = gst_element_get_static_pad (capsfilter, "sink");

  if (!otherpad)
  {
    g_set_error (data->error, FS_ERROR, FS_ERROR_CONSTRUCTION,
        "Could not get sink pad on capsfilter");
    goto error;
  }

  if (GST_PAD_LINK_FAILED (gst_pad_link (pad, otherpad)))
  {
    g_set_error (data->error, FS_ERROR, FS_ERROR_CONSTRUCTION,
        "Could not get sink pad on capsfilter");
    gst_object_unref (otherpad);
    goto error;
  }
  gst_object_unref (otherpad);

  if (!gst_element_link_pads (capsfilter, NULL,
          data->session->priv->rtpmuxer, "sink_%u"))
  {
    g_set_error (data->error, FS_ERROR, FS_ERROR_CONSTRUCTION,
        "Could not an extra capsfilter to the muxer");
    goto error;
  }


  if (!gst_element_sync_state_with_parent (capsfilter))
  {
    g_set_error (data->error, FS_ERROR, FS_ERROR_CONSTRUCTION,
        "Could not sync the state of the extra send capsfilter"
        " with the state of the conference");
    goto error;
  }

  data->other_codecs = g_list_append (data->other_codecs, filter_caps);

  return TRUE;

 error:

  g_value_set_boolean (ret, FALSE);
  gst_bin_remove (GST_BIN (data->session->priv->conference), capsfilter);
  data->session->priv->extra_send_capsfilters =
    g_list_remove (data->session->priv->extra_send_capsfilters,
        capsfilter);
  gst_caps_unref (filter_caps);

  return FALSE;
}
