parse_cod (GstJP2kDecimator * self, GstByteReader * reader,
    CodingStyleDefault * cod, guint16 length)
{
  guint8 Scod;

  if (length < 12) {
    GST_ERROR_OBJECT (self, "Invalid COD marker");
    return GST_FLOW_ERROR;
  }

  Scod = gst_byte_reader_get_uint8_unchecked (reader);
  cod->sop = ! !(Scod & 0x02);
  cod->eph = ! !(Scod & 0x04);


  cod->progression_order = gst_byte_reader_get_uint8_unchecked (reader);
  cod->n_layers = gst_byte_reader_get_uint16_be_unchecked (reader);
  cod->multi_component_transform = gst_byte_reader_get_uint8_unchecked (reader);


  cod->n_decompositions = gst_byte_reader_get_uint8_unchecked (reader);
  cod->xcb = gst_byte_reader_get_uint8_unchecked (reader) + 2;
  cod->ycb = gst_byte_reader_get_uint8_unchecked (reader) + 2;
  cod->code_block_style = gst_byte_reader_get_uint8_unchecked (reader);
  cod->transformation = gst_byte_reader_get_uint8_unchecked (reader);

  if ((Scod & 0x01)) {
    gint i;


    if (length < 12 + (Scod & 0x01) * (cod->n_decompositions + 1)) {
      GST_ERROR_OBJECT (self, "Invalid COD marker");
      return GST_FLOW_ERROR;
    }

    cod->PPx = g_slice_alloc (sizeof (guint8) * (cod->n_decompositions + 1));
    for (i = 0; i < cod->n_decompositions + 1; i++) {
      guint8 v = gst_byte_reader_get_uint8_unchecked (reader);
      cod->PPx[i] = (v & 0x0f);
      cod->PPy[i] = (v >> 4);
    }
  }

  return GST_FLOW_OK;
}
