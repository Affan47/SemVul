gst_pad_push_data (GstPad * pad, GstPadProbeType type, void *data)
{
  GstPad *peer;
  GstFlowReturn ret;

  GST_OBJECT_LOCK (pad);
  if (G_UNLIKELY (GST_PAD_IS_FLUSHING (pad)))
    goto flushing;

  if (G_UNLIKELY (GST_PAD_IS_EOS (pad)))
    goto eos;

  if (G_UNLIKELY (GST_PAD_MODE (pad) != GST_PAD_MODE_PUSH))
    goto wrong_mode;

#ifndef G_DISABLE_ASSERT
  if (!find_event_by_type (pad, GST_EVENT_STREAM_START, 0)) {
    g_warning (G_STRLOC
        ":%s:<%s:%s> Got data flow before stream-start event",
        G_STRFUNC, GST_DEBUG_PAD_NAME (pad));
  }
  if (!find_event_by_type (pad, GST_EVENT_SEGMENT, 0)) {
    g_warning (G_STRLOC
        ":%s:<%s:%s> Got data flow before segment event",
        G_STRFUNC, GST_DEBUG_PAD_NAME (pad));
  }
#endif

  if (G_UNLIKELY ((ret = check_sticky (pad, NULL))) != GST_FLOW_OK)
    goto events_error;


  PROBE_PUSH (pad, type | GST_PAD_PROBE_TYPE_BLOCK, data, probe_stopped);


  if (G_UNLIKELY ((ret = check_sticky (pad, NULL))) != GST_FLOW_OK)
    goto events_error;


  PROBE_PUSH (pad, type, data, probe_stopped);

  if (G_UNLIKELY ((peer = GST_PAD_PEER (pad)) == NULL))
    goto not_linked;


  gst_object_ref (peer);
  pad->priv->using++;
  GST_OBJECT_UNLOCK (pad);

  ret = gst_pad_chain_data_unchecked (peer, type, data);

  gst_object_unref (peer);

  GST_OBJECT_LOCK (pad);
  pad->priv->using--;
  if (pad->priv->using == 0) {

    PROBE_NO_DATA (pad, GST_PAD_PROBE_TYPE_PUSH | GST_PAD_PROBE_TYPE_IDLE,
        probe_stopped, ret);
  }
  GST_OBJECT_UNLOCK (pad);

  return ret;


flushing:
  {
    GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad,
        "pushing, but pad was flushing");
    GST_OBJECT_UNLOCK (pad);
    gst_mini_object_unref (GST_MINI_OBJECT_CAST (data));
    return GST_FLOW_FLUSHING;
  }
eos:
  {
    GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad, "pushing, but pad was EOS");
    GST_OBJECT_UNLOCK (pad);
    gst_mini_object_unref (GST_MINI_OBJECT_CAST (data));
    return GST_FLOW_EOS;
  }
wrong_mode:
  {
    g_critical ("pushing on pad %s:%s but it was not activated in push mode",
        GST_DEBUG_PAD_NAME (pad));
    GST_OBJECT_UNLOCK (pad);
    gst_mini_object_unref (GST_MINI_OBJECT_CAST (data));
    return GST_FLOW_ERROR;
  }
events_error:
  {
    GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad,
        "error pushing events, return %s", gst_flow_get_name (ret));
    GST_OBJECT_UNLOCK (pad);
    gst_mini_object_unref (GST_MINI_OBJECT_CAST (data));
    return ret;
  }
probe_stopped:
  {
    GST_OBJECT_UNLOCK (pad);
    gst_mini_object_unref (GST_MINI_OBJECT_CAST (data));

    switch (ret) {
      case GST_FLOW_CUSTOM_SUCCESS:
        GST_DEBUG_OBJECT (pad, "dropped buffer");
        ret = GST_FLOW_OK;
        break;
      default:
        GST_DEBUG_OBJECT (pad, "an error occured %s", gst_flow_get_name (ret));
        break;
    }
    return ret;
  }
not_linked:
  {
    GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad,
        "pushing, but it was not linked");
    GST_OBJECT_UNLOCK (pad);
    gst_mini_object_unref (GST_MINI_OBJECT_CAST (data));
    return GST_FLOW_NOT_LINKED;
  }
}
