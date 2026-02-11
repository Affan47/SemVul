_parse_bat (GstMpegTsSection * section)
{
  GstMpegTsBAT *bat = NULL;
  guint i = 0, allocated_streams = 12;
  guint8 *data, *end, *entry_begin;
  guint16 descriptors_loop_length, transport_stream_loop_length;

  GST_DEBUG ("BAT");

  bat = g_slice_new0 (GstMpegTsBAT);

  data = section->data;
  end = data + section->section_length;


  data += 8;

  descriptors_loop_length = GST_READ_UINT16_BE (data) & 0x0FFF;
  data += 2;


  if (descriptors_loop_length && (data + descriptors_loop_length > end - 4)) {
    GST_WARNING ("PID %d invalid BAT descriptors loop length %d",
        section->pid, descriptors_loop_length);
    goto error;
  }
  bat->descriptors =
      gst_mpegts_parse_descriptors (data, descriptors_loop_length);
  if (bat->descriptors == NULL)
    goto error;
  data += descriptors_loop_length;

  transport_stream_loop_length = GST_READ_UINT16_BE (data) & 0x0FFF;
  data += 2;
  if (G_UNLIKELY (transport_stream_loop_length > (end - 4 - data))) {
    GST_WARNING
        ("PID 0x%04x invalid BAT (transport_stream_loop_length too big)",
        section->pid);
    goto error;
  }

  bat->streams =
      g_ptr_array_new_full (allocated_streams,
      (GDestroyNotify) _gst_mpegts_bat_stream_free);


  while (transport_stream_loop_length - 4 > 0) {
    GstMpegTsBATStream *stream = g_slice_new0 (GstMpegTsBATStream);

    g_ptr_array_add (bat->streams, stream);

    if (transport_stream_loop_length < 6) {

      GST_WARNING ("PID %d invalid BAT entry size %d",
          section->pid, transport_stream_loop_length);
      goto error;
    }

    entry_begin = data;

    stream->transport_stream_id = GST_READ_UINT16_BE (data);
    data += 2;

    stream->original_network_id = GST_READ_UINT16_BE (data);
    data += 2;

    descriptors_loop_length = GST_READ_UINT16_BE (data) & 0x0FFF;
    data += 2;

    GST_DEBUG ("descriptors_loop_length %d", descriptors_loop_length);

    if (descriptors_loop_length && (data + descriptors_loop_length > end - 4)) {
      GST_WARNING
          ("PID %d invalid BAT entry %d descriptors loop length %d (only have %"
          G_GSIZE_FORMAT ")", section->pid, section->subtable_extension,
          descriptors_loop_length, end - 4 - data);
      goto error;
    }
    stream->descriptors =
        gst_mpegts_parse_descriptors (data, descriptors_loop_length);
    if (stream->descriptors == NULL)
      goto error;

    data += descriptors_loop_length;

    i += 1;
    transport_stream_loop_length -= data - entry_begin;
  }

  if (data != end - 4) {
    GST_WARNING ("PID %d invalid BAT parsed %d length %d",
        section->pid, (gint) (data - section->data), section->section_length);
    goto error;
  }

  return (gpointer) bat;

error:
  if (bat)
    _gst_mpegts_bat_free (bat);

  return NULL;
}
