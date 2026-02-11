qtdemux_dump_stsz (GstQTDemux * qtdemux, GstByteReader * data, int depth)
{
  guint32 ver_flags = 0, sample_size = 0, num_entries = 0;

  if (!gst_byte_reader_get_uint32_be (data, &ver_flags) ||
      !gst_byte_reader_get_uint32_be (data, &sample_size))
    return FALSE;

  GST_LOG ("%*s  version/flags: %08x", depth, "", ver_flags);
  GST_LOG ("%*s  sample size:   %d", depth, "", sample_size);

  if (sample_size == 0) {
    if (!gst_byte_reader_get_uint32_be (data, &num_entries))
      return FALSE;

    GST_LOG ("%*s  n entries:     %d", depth, "", num_entries);
#if 0
    if (!qt_atom_parser_has_chunks (data, num_entries, 4))
      return FALSE;
    for (i = 0; i < num_entries; i++) {
      GST_LOG ("%*s    sample size:   %u", depth, "", GET_UINT32 (data));
    }
#endif
  }
  return TRUE;
}
