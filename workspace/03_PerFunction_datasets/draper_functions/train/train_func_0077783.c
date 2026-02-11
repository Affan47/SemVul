gst_ebml_write_sint (GstEbmlWrite * ebml, guint32 id, gint64 num)
{
  GstBuffer *buf;
  guint8 *data_start, *data_end;
  GstMapInfo map;


  guint64 unum = (num < 0 ? (-num - 1) << 1 : num << 1);
  guint size = gst_ebml_write_get_uint_size (unum);

  buf = gst_ebml_write_element_new (ebml, &map, sizeof (num));
  data_end = data_start = map.data;


  if (num >= 0) {
    unum = num;
  } else {
    unum = 0x80 << (size - 1);
    unum += num;
    unum |= 0x80 << (size - 1);
  }


  gst_ebml_write_element_id (&data_end, id);
  gst_ebml_write_element_size (&data_end, size);
  gst_ebml_write_set_uint (&data_end, unum, size);
  gst_buffer_unmap (buf, &map);
  gst_buffer_set_size (buf, (data_end - data_start));

  gst_ebml_write_element_push (ebml, buf, data_start, data_end);
}
