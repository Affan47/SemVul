gst_interlace_init (GstInterlace * interlace)
{
  GST_DEBUG ("gst_interlace_init");
  interlace->sinkpad =
      gst_pad_new_from_static_template (&gst_interlace_sink_template, "sink");
  gst_element_add_pad (GST_ELEMENT (interlace), interlace->sinkpad);
  gst_pad_set_chain_function (interlace->sinkpad, gst_interlace_chain);
  gst_pad_set_setcaps_function (interlace->sinkpad, gst_interlace_setcaps);
  gst_pad_set_getcaps_function (interlace->sinkpad, gst_interlace_getcaps);
  gst_pad_set_event_function (interlace->sinkpad, gst_interlace_sink_event);

  interlace->srcpad =
      gst_pad_new_from_static_template (&gst_interlace_src_template, "src");
  gst_element_add_pad (GST_ELEMENT (interlace), interlace->srcpad);
  gst_pad_set_setcaps_function (interlace->srcpad, gst_interlace_setcaps);
  gst_pad_set_getcaps_function (interlace->srcpad, gst_interlace_getcaps);

  interlace->top_field_first = FALSE;
  interlace->allow_rff = FALSE;
  interlace->pattern = GST_INTERLACE_PATTERN_2_3;
  interlace->pattern_offset = 0;
  gst_interlace_reset (interlace);
}
