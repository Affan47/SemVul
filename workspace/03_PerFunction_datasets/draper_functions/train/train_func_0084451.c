gst_pad_proxy_query_caps (GstPad * pad, GstQuery * query)
{
  GstCaps *filter, *templ, *result;
  QueryCapsData data;

  g_return_val_if_fail (GST_IS_PAD (pad), FALSE);
  g_return_val_if_fail (GST_IS_QUERY (query), FALSE);
  g_return_val_if_fail (GST_QUERY_TYPE (query) == GST_QUERY_CAPS, FALSE);

  GST_CAT_DEBUG_OBJECT (GST_CAT_PADS, pad, "proxying caps query for %s:%s",
      GST_DEBUG_PAD_NAME (pad));

  data.query = query;


  gst_query_parse_caps (query, &filter);
  data.ret = filter ? gst_caps_ref (filter) : gst_caps_new_any ();

  gst_pad_forward (pad, (GstPadForwardFunction) query_caps_func, &data);

  templ = gst_pad_get_pad_template_caps (pad);
  result = gst_caps_intersect (data.ret, templ);
  gst_caps_unref (data.ret);
  gst_caps_unref (templ);

  gst_query_set_caps_result (query, result);
  gst_caps_unref (result);

  return TRUE;
}
