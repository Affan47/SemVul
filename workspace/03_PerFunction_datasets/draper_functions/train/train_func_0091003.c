gst_pad_proxy_query_accept_caps (GstPad * pad, GstQuery * query)
{
  QueryAcceptCapsData data;

  g_return_val_if_fail (GST_IS_PAD (pad), FALSE);
  g_return_val_if_fail (GST_IS_QUERY (query), FALSE);
  g_return_val_if_fail (GST_QUERY_TYPE (query) == GST_QUERY_ACCEPT_CAPS, FALSE);

  GST_CAT_DEBUG_OBJECT (GST_CAT_PADS, pad,
      "proxying accept caps query for %s:%s", GST_DEBUG_PAD_NAME (pad));

  data.query = query;

  data.ret = TRUE;

  gst_pad_forward (pad, (GstPadForwardFunction) query_accept_caps_func, &data);
  gst_query_set_accept_caps_result (query, data.ret);

  return TRUE;
}
