gst_proxy_pad_chain_list_default (GstPad * pad, GstObject * parent,
    GstBufferList * list)
{
  GstFlowReturn res;
  GstPad *internal;

  g_return_val_if_fail (GST_IS_PROXY_PAD (pad), GST_FLOW_ERROR);
  g_return_val_if_fail (GST_IS_BUFFER_LIST (list), GST_FLOW_ERROR);

  GST_PROXY_PAD_ACQUIRE_INTERNAL (pad, internal, GST_FLOW_NOT_LINKED);
  res = gst_pad_push_list (internal, list);
  GST_PROXY_PAD_RELEASE_INTERNAL (internal);

  return res;
}
