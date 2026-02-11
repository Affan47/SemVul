gst_vc1_parse_sequence_header_struct_c (const guint8 * data, gsize size,
    GstVC1SeqStructC * structc)
{
  GstBitReader br = GST_BIT_READER_INIT (data, size);

  g_return_val_if_fail (structc != NULL, GST_VC1_PARSER_ERROR);

  return parse_sequence_header_struct_c (&br, structc);
}
