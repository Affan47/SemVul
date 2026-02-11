gst_play_sink_refresh_pad (GstPlaySink * playsink, GstPad * pad,
    GstPlaySinkType type)
{
  gulong *block_id = NULL;

  GST_DEBUG_OBJECT (playsink, "refresh pad %" GST_PTR_FORMAT, pad);

  GST_PLAY_SINK_LOCK (playsink);
  if (pad == playsink->video_pad) {
    if (type != GST_PLAY_SINK_TYPE_VIDEO_RAW &&
        type != GST_PLAY_SINK_TYPE_VIDEO)
      goto wrong_type;
    block_id = &playsink->video_block_id;
  } else if (pad == playsink->audio_pad) {
    if (type != GST_PLAY_SINK_TYPE_AUDIO_RAW &&
        type != GST_PLAY_SINK_TYPE_AUDIO)
      goto wrong_type;
    block_id = &playsink->audio_block_id;
  } else if (pad == playsink->text_pad) {
    if (type != GST_PLAY_SINK_TYPE_TEXT)
      goto wrong_type;
    block_id = &playsink->text_block_id;
  }

  if (type != GST_PLAY_SINK_TYPE_FLUSHING && (block_id && *block_id == 0)) {
    GstPad *blockpad =
        GST_PAD_CAST (gst_proxy_pad_get_internal (GST_PROXY_PAD (pad)));

    if (playsink->vis_pad_block_id)
      gst_pad_remove_probe (((GstPlayVisChain *) playsink->vischain)->blockpad,
          playsink->vis_pad_block_id);
    playsink->vis_pad_block_id = 0;

    *block_id =
        gst_pad_add_probe (blockpad, GST_PAD_PROBE_TYPE_BLOCK_DOWNSTREAM,
        sinkpad_blocked_cb, playsink, NULL);
    PENDING_FLAG_SET (playsink, type);
    gst_object_unref (blockpad);
  }
  GST_PLAY_SINK_UNLOCK (playsink);

  return;


wrong_type:
  {
    GST_WARNING_OBJECT (playsink, "wrong type %u for pad %" GST_PTR_FORMAT,
        type, pad);
    GST_PLAY_SINK_UNLOCK (playsink);
    return;
  }
}
