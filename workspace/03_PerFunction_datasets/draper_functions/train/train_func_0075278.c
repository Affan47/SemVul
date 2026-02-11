gst_dca_parse_parse_frame (GstBaseParse * parse, GstBaseParseFrame * frame)
{
  GstDcaParse *dcaparse = GST_DCA_PARSE (parse);
  GstBuffer *buf = frame->buffer;
  GstByteReader r = GST_BYTE_READER_INIT_FROM_BUFFER (buf);
  guint size, rate, chans, depth, block_size, num_blocks, samples_per_block;
  gint endianness;
  gboolean terminator;

  if (!gst_dca_parse_parse_header (dcaparse, &r, &size, &rate, &chans, &depth,
          &endianness, &num_blocks, &samples_per_block, &terminator))
    goto broken_header;

  block_size = num_blocks * samples_per_block;

  if (G_UNLIKELY (dcaparse->rate != rate || dcaparse->channels != chans
          || dcaparse->depth != depth || dcaparse->endianness != endianness
          || (!terminator && dcaparse->block_size != block_size)
          || (size != dcaparse->frame_size))) {
    GstCaps *caps;

    caps = gst_caps_new_simple ("audio/x-dts",
        "framed", G_TYPE_BOOLEAN, TRUE,
        "rate", G_TYPE_INT, rate, "channels", G_TYPE_INT, chans,
        "endianness", G_TYPE_INT, endianness, "depth", G_TYPE_INT, depth,
        "block-size", G_TYPE_INT, block_size, "frame-size", G_TYPE_INT, size,
        NULL);
    gst_buffer_set_caps (buf, caps);
    gst_pad_set_caps (GST_BASE_PARSE_SRC_PAD (parse), caps);
    gst_caps_unref (caps);

    dcaparse->rate = rate;
    dcaparse->channels = chans;
    dcaparse->depth = depth;
    dcaparse->endianness = endianness;
    dcaparse->block_size = block_size;
    dcaparse->frame_size = size;

    gst_base_parse_set_frame_rate (parse, rate, block_size, 0, 0);
  }

  return GST_FLOW_OK;


broken_header:
  {

    GST_ELEMENT_ERROR (parse, STREAM, DECODE, (NULL), (NULL));
    return GST_FLOW_ERROR;
  }
}
