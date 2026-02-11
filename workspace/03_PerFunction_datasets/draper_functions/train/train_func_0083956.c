gst_rnd_buffer_size_chain (GstPad * pad, GstObject * parent, GstBuffer * buf)
{
  GstRndBufferSize *rnd = GST_RND_BUFFER_SIZE (parent);
  GstFlowReturn flow;

  if (rnd->adapter == NULL)
    rnd->adapter = gst_adapter_new ();

  gst_adapter_push (rnd->adapter, buf);

  flow = gst_rnd_buffer_size_drain_adapter (rnd, FALSE);

  if (flow != GST_FLOW_OK)
    GST_INFO_OBJECT (rnd, "flow: %s", gst_flow_get_name (flow));

  return flow;
}
