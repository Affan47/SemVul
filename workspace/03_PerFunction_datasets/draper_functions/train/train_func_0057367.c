gst_asf_parse_pull_indexes (GstAsfParse * asfparse)
{
  GstBuffer *guid_and_size = NULL;
  GstBuffer *buf = NULL;
  guint64 obj_size;
  GstFlowReturn ret = GST_FLOW_OK;
  while (1) {
    ret = gst_pad_pull_range (asfparse->sinkpad, asfparse->offset,
        ASF_GUID_OBJSIZE_SIZE, &guid_and_size);
    if (ret != GST_FLOW_OK)
      break;

    obj_size =
        gst_asf_match_and_peek_obj_size (GST_BUFFER_DATA (guid_and_size), NULL);
    if (obj_size == 0) {
      GST_ERROR_OBJECT (asfparse, "Incomplete object found");
      gst_buffer_unref (guid_and_size);
      ret = GST_FLOW_ERROR;
      break;
    }
    asfparse->offset += ASF_GUID_OBJSIZE_SIZE;


    ret = gst_pad_pull_range (asfparse->sinkpad, asfparse->offset, obj_size,
        &buf);
    if (ret != GST_FLOW_OK) {
      gst_buffer_unref (guid_and_size);
      break;
    }
    asfparse->offset += obj_size - ASF_GUID_OBJSIZE_SIZE;

    buf = gst_buffer_join (guid_and_size, buf);
    ret = gst_asf_parse_push (asfparse, buf);
    if (ret != GST_FLOW_OK)
      break;
  }
  return ret;
}
