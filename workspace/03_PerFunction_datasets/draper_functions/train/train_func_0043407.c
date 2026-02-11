gst_pad_pull_range (GstPad * pad, guint64 offset, guint size,
    GstBuffer ** buffer)
{
  GstPad *peer;
  GstFlowReturn ret;
  GstBuffer *res_buf;

  g_return_val_if_fail (GST_IS_PAD (pad), GST_FLOW_ERROR);
  g_return_val_if_fail (GST_PAD_IS_SINK (pad), GST_FLOW_ERROR);
  g_return_val_if_fail (buffer != NULL, GST_FLOW_ERROR);
  g_return_val_if_fail (*buffer == NULL
      || GST_IS_BUFFER (*buffer), GST_FLOW_ERROR);

  GST_OBJECT_LOCK (pad);
  if (G_UNLIKELY (GST_PAD_IS_FLUSHING (pad)))
    goto flushing;

  if (G_UNLIKELY (GST_PAD_MODE (pad) != GST_PAD_MODE_PULL))
    goto wrong_mode;

  res_buf = *buffer;


  PROBE_PULL (pad, GST_PAD_PROBE_TYPE_PULL | GST_PAD_PROBE_TYPE_BLOCK,
      res_buf, offset, size, probe_stopped);

  if (G_UNLIKELY ((peer = GST_PAD_PEER (pad)) == NULL))
    goto not_linked;

  gst_object_ref (peer);
  pad->priv->using++;
  GST_OBJECT_UNLOCK (pad);

  ret = gst_pad_get_range_unchecked (peer, offset, size, &res_buf);

  gst_object_unref (peer);

  GST_OBJECT_LOCK (pad);
  pad->priv->using--;
  if (pad->priv->using == 0) {

    PROBE_NO_DATA (pad, GST_PAD_PROBE_TYPE_PULL | GST_PAD_PROBE_TYPE_IDLE,
        probe_stopped_unref, ret);
  }

  if (G_UNLIKELY (ret != GST_FLOW_OK))
    goto pull_range_failed;

probed_data:
  PROBE_PULL (pad, GST_PAD_PROBE_TYPE_PULL | GST_PAD_PROBE_TYPE_BUFFER,
      res_buf, offset, size, probe_stopped_unref);

  GST_OBJECT_UNLOCK (pad);

  *buffer = res_buf;

  return ret;


flushing:
  {
    GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad,
        "pullrange, but pad was flushing");
    GST_OBJECT_UNLOCK (pad);
    return GST_FLOW_FLUSHING;
  }
wrong_mode:
  {
    g_critical ("pullrange on pad %s:%s but it was not activated in pull mode",
        GST_DEBUG_PAD_NAME (pad));
    GST_OBJECT_UNLOCK (pad);
    return GST_FLOW_ERROR;
  }
probe_stopped:
  {
    GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad, "pre probe returned %s",
        gst_flow_get_name (ret));
    if (ret == GST_FLOW_CUSTOM_SUCCESS) {
      if (res_buf) {


        GST_DEBUG_OBJECT (pad, "handled buffer");
        ret = GST_FLOW_OK;
        goto probed_data;
      } else {

        GST_DEBUG_OBJECT (pad, "no buffer, return EOS");
        ret = GST_FLOW_EOS;
      }
    }
    GST_OBJECT_UNLOCK (pad);
    return ret;
  }
not_linked:
  {
    GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad,
        "pulling range, but it was not linked");
    GST_OBJECT_UNLOCK (pad);
    return GST_FLOW_NOT_LINKED;
  }
pull_range_failed:
  {
    GST_OBJECT_UNLOCK (pad);
    GST_CAT_LEVEL_LOG (GST_CAT_SCHEDULING,
        (ret >= GST_FLOW_EOS) ? GST_LEVEL_INFO : GST_LEVEL_WARNING,
        pad, "pullrange failed, flow: %s", gst_flow_get_name (ret));
    return ret;
  }
probe_stopped_unref:
  {
    GST_CAT_LOG_OBJECT (GST_CAT_SCHEDULING, pad,
        "post probe returned %s", gst_flow_get_name (ret));
    GST_OBJECT_UNLOCK (pad);

    if (ret == GST_FLOW_CUSTOM_SUCCESS)
      ret = GST_FLOW_EOS;
    if (*buffer == NULL)
      gst_buffer_unref (res_buf);
    return ret;
  }
}
