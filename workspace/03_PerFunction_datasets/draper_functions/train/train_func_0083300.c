gst_chop_my_data_chain (GstPad * pad, GstBuffer * buffer)
{
  GstChopMyData *chopmydata;
  GstFlowReturn ret;

  chopmydata = GST_CHOP_MY_DATA (gst_pad_get_parent (pad));

  GST_DEBUG_OBJECT (chopmydata, "chain");

  gst_adapter_push (chopmydata->adapter, buffer);
  ret = gst_chop_my_data_process (chopmydata, FALSE);

  gst_object_unref (chopmydata);
  return ret;
}
