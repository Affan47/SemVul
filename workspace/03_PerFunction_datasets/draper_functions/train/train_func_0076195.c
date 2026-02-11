mxf_up_write_func (GstBuffer * buffer, GstCaps * caps, gpointer mapping_data,
    GstAdapter * adapter, GstBuffer ** outbuf, gboolean flush)
{
  MXFUPMappingData *data = mapping_data;

  if (!buffer)
    return GST_FLOW_OK;

  if (GST_BUFFER_SIZE (buffer) !=
      GST_ROUND_UP_4 (data->bpp * data->width) * data->height) {
    GST_ERROR ("Invalid buffer size");
    return GST_FLOW_ERROR;
  }

  if (data->bpp != 4
      || GST_ROUND_UP_4 (data->width * data->bpp) != data->width * data->bpp) {
    guint y;
    GstBuffer *ret;
    guint8 *indata, *outdata;

    ret = gst_buffer_new_and_alloc (data->width * data->bpp * data->height);
    indata = GST_BUFFER_DATA (buffer);
    outdata = GST_BUFFER_DATA (ret);

    for (y = 0; y < data->height; y++) {
      memcpy (outdata, indata, data->width * data->bpp);
      indata += GST_ROUND_UP_4 (data->width * data->bpp);
      outdata += data->width * data->bpp;
    }

    gst_buffer_unref (buffer);

    *outbuf = ret;
  } else {
    *outbuf = buffer;
  }

  return GST_FLOW_OK;
}
