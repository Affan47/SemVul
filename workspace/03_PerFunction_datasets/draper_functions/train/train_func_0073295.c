gst_base_transform_activate (GstBaseTransform * trans, gboolean active)
{
  GstBaseTransformClass *bclass;
  gboolean result = TRUE;

  bclass = GST_BASE_TRANSFORM_GET_CLASS (trans);

  GST_OBJECT_LOCK (trans);
  gst_base_transform_clear_transformed_caps_cache (trans);
  GST_OBJECT_UNLOCK (trans);

  if (active) {
    if (trans->priv->pad_mode == GST_ACTIVATE_NONE && bclass->start)
      result &= bclass->start (trans);

    GST_OBJECT_LOCK (trans);

    if (GST_PAD_CAPS (trans->sinkpad) && GST_PAD_CAPS (trans->srcpad))
      trans->have_same_caps =
          gst_caps_is_equal (GST_PAD_CAPS (trans->sinkpad),
          GST_PAD_CAPS (trans->srcpad)) || trans->passthrough;
    else
      trans->have_same_caps = trans->passthrough;
    GST_DEBUG_OBJECT (trans, "have_same_caps %d", trans->have_same_caps);
    trans->negotiated = FALSE;
    trans->have_newsegment = FALSE;
    gst_segment_init (&trans->segment, GST_FORMAT_UNDEFINED);
    trans->priv->last_stop_out = GST_CLOCK_TIME_NONE;
    trans->priv->proportion = 1.0;
    trans->priv->earliest_time = -1;
    trans->priv->discont = FALSE;
    gst_caps_replace (&trans->priv->sink_suggest, NULL);
    trans->priv->processed = 0;
    trans->priv->dropped = 0;
    trans->priv->force_alloc = TRUE;

    GST_OBJECT_UNLOCK (trans);
  } else {


    GST_PAD_STREAM_LOCK (trans->sinkpad);
    GST_PAD_STREAM_UNLOCK (trans->sinkpad);

    gst_base_transform_drop_delayed_events (trans);

    trans->have_same_caps = FALSE;


    if (bclass->passthrough_on_same_caps) {
      gst_base_transform_set_passthrough (trans, FALSE);
    }
    gst_caps_replace (&trans->cache_caps1, NULL);
    gst_caps_replace (&trans->cache_caps2, NULL);
    gst_caps_replace (&trans->priv->sink_alloc, NULL);
    gst_caps_replace (&trans->priv->sink_suggest, NULL);

    if (trans->priv->pad_mode != GST_ACTIVATE_NONE && bclass->stop)
      result &= bclass->stop (trans);
  }

  return result;
}
