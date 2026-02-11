pad_removed_cb (GstElement * decodebin, GstPad * pad, GstSourceGroup * group)
{
  GstPlayBin *playbin;
  GstPad *peer;
  GstElement *combiner;
  GstSourceCombine *combine;
  int signal = -1;
  gulong group_id_probe_handler;

  playbin = group->playbin;

  GST_DEBUG_OBJECT (playbin,
      "pad %s:%s removed from group %p", GST_DEBUG_PAD_NAME (pad), group);

  GST_SOURCE_GROUP_LOCK (group);

  if ((group_id_probe_handler =
          (guintptr) g_object_get_data (G_OBJECT (pad),
              "playbin.event_probe_id"))) {
    gst_pad_remove_probe (pad, group_id_probe_handler);
    g_object_set_data (G_OBJECT (pad), "playbin.event_probe_id", 0);
  }

  if ((combine = g_object_get_data (G_OBJECT (pad), "playbin.combine"))) {
    g_assert (combine->combiner == NULL);
    g_assert (combine->srcpad == pad);
    gst_object_unref (pad);
    combine->srcpad = NULL;
    goto exit;
  }


  if (!(peer = g_object_get_data (G_OBJECT (pad), "playbin.sinkpad")))
    goto not_linked;

  if ((combine = g_object_get_data (G_OBJECT (peer), "playbin.combine"))) {
    if (combine->has_tags) {
      gulong notify_tags_handler;

      notify_tags_handler =
          (guintptr) g_object_get_data (G_OBJECT (peer),
          "playbin.notify_tags_handler");
      if (notify_tags_handler != 0)
        g_signal_handler_disconnect (G_OBJECT (peer), notify_tags_handler);
      g_object_set_data (G_OBJECT (peer), "playbin.notify_tags_handler", NULL);
    }


    g_ptr_array_remove (combine->channels, peer);
    GST_DEBUG_OBJECT (playbin, "pad %p removed from array", peer);


    switch (combine->type) {
      case GST_PLAY_SINK_TYPE_VIDEO:
      case GST_PLAY_SINK_TYPE_VIDEO_RAW:
        signal = SIGNAL_VIDEO_CHANGED;
        break;
      case GST_PLAY_SINK_TYPE_AUDIO:
      case GST_PLAY_SINK_TYPE_AUDIO_RAW:
        signal = SIGNAL_AUDIO_CHANGED;
        break;
      case GST_PLAY_SINK_TYPE_TEXT:
        signal = SIGNAL_TEXT_CHANGED;
        break;
      default:
        signal = -1;
    }

    if (!combine->channels->len && combine->combiner) {
      GST_DEBUG_OBJECT (playbin, "all combiner sinkpads removed");
      GST_DEBUG_OBJECT (playbin, "removing combiner %p", combine->combiner);
      gst_object_unref (combine->srcpad);
      combine->srcpad = NULL;
      gst_element_set_state (combine->combiner, GST_STATE_NULL);
      gst_bin_remove (GST_BIN_CAST (playbin), combine->combiner);
      combine->combiner = NULL;
    }
  }


  gst_pad_unlink (pad, peer);


  combiner = GST_ELEMENT_CAST (gst_pad_get_parent (peer));
  if (!combiner) {
    gst_object_unref (peer);
    goto no_combiner;
  }


  gst_element_release_request_pad (combiner, peer);
  gst_object_unref (peer);

  gst_object_unref (combiner);
exit:
  GST_SOURCE_GROUP_UNLOCK (group);

  if (signal >= 0)
    g_signal_emit (G_OBJECT (playbin), gst_play_bin_signals[signal], 0, NULL);

  return;


not_linked:
  {
    GST_DEBUG_OBJECT (playbin, "pad not linked");
    goto exit;
  }
no_combiner:
  {
    GST_DEBUG_OBJECT (playbin, "combiner not found");
    goto exit;
  }
}
