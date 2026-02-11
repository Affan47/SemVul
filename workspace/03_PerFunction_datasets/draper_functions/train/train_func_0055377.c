gst_pad_query (GstPad * pad, GstQuery * query)
{
  GstObject *parent;
  gboolean res, serialized;
  GstPadQueryFunction func;
  GstPadProbeType type;
  GstFlowReturn ret;

  g_return_val_if_fail (GST_IS_PAD (pad), FALSE);
  g_return_val_if_fail (GST_IS_QUERY (query), FALSE);

  if (GST_PAD_IS_SRC (pad)) {
    if (G_UNLIKELY (!GST_QUERY_IS_UPSTREAM (query)))
      goto wrong_direction;
    type = GST_PAD_PROBE_TYPE_QUERY_UPSTREAM;
  } else if (GST_PAD_IS_SINK (pad)) {
    if (G_UNLIKELY (!GST_QUERY_IS_DOWNSTREAM (query)))
      goto wrong_direction;
    type = GST_PAD_PROBE_TYPE_QUERY_DOWNSTREAM;
  } else
    goto unknown_direction;

  GST_DEBUG_OBJECT (pad, "doing query %p (%s)", query,
      GST_QUERY_TYPE_NAME (query));

  serialized = GST_QUERY_IS_SERIALIZED (query);
  if (G_UNLIKELY (serialized))
    GST_PAD_STREAM_LOCK (pad);

  GST_OBJECT_LOCK (pad);
  PROBE_PUSH (pad, type | GST_PAD_PROBE_TYPE_PUSH |
      GST_PAD_PROBE_TYPE_BLOCK, query, probe_stopped);
  PROBE_PUSH (pad, type | GST_PAD_PROBE_TYPE_PUSH, query, probe_stopped);

  ACQUIRE_PARENT (pad, parent, no_parent);
  GST_OBJECT_UNLOCK (pad);

  if ((func = GST_PAD_QUERYFUNC (pad)) == NULL)
    goto no_func;

  res = func (pad, parent, query);

  RELEASE_PARENT (parent);

  GST_DEBUG_OBJECT (pad, "sent query %p (%s), result %d", query,
      GST_QUERY_TYPE_NAME (query), res);

  if (res != TRUE)
    goto query_failed;

  GST_OBJECT_LOCK (pad);
  PROBE_PUSH (pad, type | GST_PAD_PROBE_TYPE_PULL, query, probe_stopped);
  GST_OBJECT_UNLOCK (pad);

  if (G_UNLIKELY (serialized))
    GST_PAD_STREAM_UNLOCK (pad);

  return res;


wrong_direction:
  {
    g_warning ("pad %s:%s query %s in wrong direction",
        GST_DEBUG_PAD_NAME (pad), GST_QUERY_TYPE_NAME (query));
    return FALSE;
  }
unknown_direction:
  {
    g_warning ("pad %s:%s has invalid direction", GST_DEBUG_PAD_NAME (pad));
    return FALSE;
  }
no_parent:
  {
    GST_DEBUG_OBJECT (pad, "had no parent");
    GST_OBJECT_UNLOCK (pad);
    if (G_UNLIKELY (serialized))
      GST_PAD_STREAM_UNLOCK (pad);
    return FALSE;
  }
no_func:
  {
    GST_DEBUG_OBJECT (pad, "had no query function");
    RELEASE_PARENT (parent);
    if (G_UNLIKELY (serialized))
      GST_PAD_STREAM_UNLOCK (pad);
    return FALSE;
  }
query_failed:
  {
    GST_DEBUG_OBJECT (pad, "query failed");
    if (G_UNLIKELY (serialized))
      GST_PAD_STREAM_UNLOCK (pad);
    return FALSE;
  }
probe_stopped:
  {
    GST_DEBUG_OBJECT (pad, "probe stopped: %s", gst_flow_get_name (ret));
    GST_OBJECT_UNLOCK (pad);
    if (G_UNLIKELY (serialized))
      GST_PAD_STREAM_UNLOCK (pad);


    if (ret == GST_FLOW_CUSTOM_SUCCESS)
      res = TRUE;
    else
      res = FALSE;

    return res;
  }
}
