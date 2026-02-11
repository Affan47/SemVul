qtdemux_dump_stsd (GstQTDemux * qtdemux, GstByteReader * data, int depth)
{
  guint32 ver_flags = 0, num_entries = 0, i;

  if (!gst_byte_reader_get_uint32_be (data, &ver_flags) ||
      !gst_byte_reader_get_uint32_be (data, &num_entries))
    return FALSE;

  GST_LOG ("%*s  version/flags: %08x", depth, "", ver_flags);
  GST_LOG ("%*s  n entries:     %d", depth, "", num_entries);

  for (i = 0; i < num_entries; i++) {
    GstByteReader sub;
    guint32 size = 0, fourcc;

    if (!gst_byte_reader_get_uint32_be (data, &size) ||
        !qt_atom_parser_get_fourcc (data, &fourcc))
      return FALSE;

    GST_LOG ("%*s    size:          %u", depth, "", size);
    GST_LOG ("%*s    type:          %" GST_FOURCC_FORMAT, depth, "",
        GST_FOURCC_ARGS (fourcc));

    if (size < (6 + 2 + 4 + 4 + 4 + 4 + 2 + 2 + 4 + 4 + 4 + 2 + 1 + 31 + 2 + 2))
      return FALSE;

    qt_atom_parser_peek_sub (data, 0, 78, &sub);
    gst_byte_reader_skip (&sub, 6);
    GST_LOG ("%*s    data reference:%d", depth, "", GET_UINT16 (&sub));
    GST_LOG ("%*s    version/rev.:  %08x", depth, "", GET_UINT32 (&sub));
    fourcc = GET_FOURCC (&sub);
    GST_LOG ("%*s    vendor:        %" GST_FOURCC_FORMAT, depth, "",
        GST_FOURCC_ARGS (fourcc));
    GST_LOG ("%*s    temporal qual: %u", depth, "", GET_UINT32 (&sub));
    GST_LOG ("%*s    spatial qual:  %u", depth, "", GET_UINT32 (&sub));
    GST_LOG ("%*s    width:         %u", depth, "", GET_UINT16 (&sub));
    GST_LOG ("%*s    height:        %u", depth, "", GET_UINT16 (&sub));
    GST_LOG ("%*s    horiz. resol:  %g", depth, "", GET_FP32 (&sub));
    GST_LOG ("%*s    vert. resol.:  %g", depth, "", GET_FP32 (&sub));
    GST_LOG ("%*s    data size:     %u", depth, "", GET_UINT32 (&sub));
    GST_LOG ("%*s    frame count:   %u", depth, "", GET_UINT16 (&sub));


    gst_byte_reader_skip (&sub, 1 + 31);
    GST_LOG ("%*s    compressor:    (skipped)", depth, "");
    GST_LOG ("%*s    depth:         %u", depth, "", GET_UINT16 (&sub));
    GST_LOG ("%*s    color table ID:%u", depth, "", GET_UINT16 (&sub));
    if (!gst_byte_reader_skip (data, size - (4 + 4)))
      return FALSE;
  }
  return TRUE;
}
