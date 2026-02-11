create_elements_and_pads (GstEncodeBin * ebin)
{
  gboolean ret = TRUE;
  GstElement *muxer = NULL;
  GstPad *muxerpad;
  const GList *tmp, *profiles;
  GstEncodingProfile *sprof;

  GST_DEBUG ("Current profile : %s",
      gst_encoding_profile_get_name (ebin->profile));

  if (GST_IS_ENCODING_CONTAINER_PROFILE (ebin->profile)) {

    muxer = _get_muxer (ebin);
    if (G_UNLIKELY (muxer == NULL))
      goto no_muxer;


    ebin->muxer = muxer;
    gst_bin_add ((GstBin *) ebin, muxer);


    muxerpad = gst_element_get_static_pad (muxer, "src");
    if (G_UNLIKELY (muxerpad == NULL))
      goto no_muxer_pad;

    if (!gst_ghost_pad_set_target (GST_GHOST_PAD (ebin->srcpad), muxerpad))
      goto no_muxer_ghost_pad;

    gst_object_unref (muxerpad);

    profiles =
        gst_encoding_container_profile_get_profiles
        (GST_ENCODING_CONTAINER_PROFILE (ebin->profile));
    for (tmp = profiles; tmp; tmp = tmp->next) {
      sprof = (GstEncodingProfile *) tmp->data;

      GST_DEBUG ("Trying stream profile with presence %d",
          gst_encoding_profile_get_presence (sprof));

      if (gst_encoding_profile_get_presence (sprof) != 0) {
        if (G_UNLIKELY (_create_stream_group (ebin, sprof, NULL, NULL) == NULL))
          goto stream_error;
      }
    }
    gst_element_sync_state_with_parent (muxer);
  } else {
    if (G_UNLIKELY (_create_stream_group (ebin, ebin->profile, NULL,
                NULL) == NULL))
      goto stream_error;
  }

  return ret;

no_muxer:
  {
    GstCaps *format = gst_encoding_profile_get_format (ebin->profile);

    GST_WARNING ("No available muxer for %" GST_PTR_FORMAT, format);

    gst_element_post_message (GST_ELEMENT_CAST (ebin),
        gst_missing_encoder_message_new (GST_ELEMENT_CAST (ebin), format));
    GST_ELEMENT_ERROR (ebin, CORE, MISSING_PLUGIN, (NULL),
        ("No available muxer for format %" GST_PTR_FORMAT, format));
    if (format)
      gst_caps_unref (format);
    return FALSE;
  }

no_muxer_pad:
  {
    GST_WARNING ("Can't get source pad from muxer (%s)",
        GST_ELEMENT_NAME (muxer));
    gst_bin_remove (GST_BIN (ebin), muxer);
    return FALSE;
  }

no_muxer_ghost_pad:
  {
    GST_WARNING ("Couldn't set %s:%s as source ghostpad target",
        GST_DEBUG_PAD_NAME (muxerpad));
    gst_bin_remove (GST_BIN (ebin), muxer);
    gst_object_unref (muxerpad);
    return FALSE;
  }

stream_error:
  {
    GST_WARNING ("Could not create Streams");
    if (muxer)
      gst_bin_remove (GST_BIN (ebin), muxer);
    ebin->muxer = NULL;
    return FALSE;
  }
}
