gst_valve_chain (GstPad * pad, GstBuffer * buffer)
{
  GstValve *valve = GST_VALVE (GST_OBJECT_PARENT (pad));
  GstFlowReturn ret = GST_FLOW_OK;

  if (g_atomic_int_get (&valve->drop)) {
    gst_buffer_unref (buffer);
    valve->discont = TRUE;
  } else {
    if (valve->discont) {
      buffer = gst_buffer_make_metadata_writable (buffer);
      GST_BUFFER_FLAG_SET (buffer, GST_BUFFER_FLAG_DISCONT);
      valve->discont = FALSE;
    }

    ret = gst_pad_push (valve->srcpad, buffer);
  }


  if (g_atomic_int_get (&valve->drop))
    ret = GST_FLOW_OK;

  return ret;
}
