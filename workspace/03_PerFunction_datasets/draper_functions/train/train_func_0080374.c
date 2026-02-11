gst_audio_convert_fixate_channels (GstBaseTransform * base, GstStructure * ins,
    GstStructure * outs)
{
  const GValue *in_layout, *out_layout;
  gint in_chans, out_chans;

  if (!gst_structure_get_int (ins, "channels", &in_chans))
    return;

  if (!gst_structure_has_field (outs, "channels")) {


    gst_structure_remove_field (outs, "channel-positions");
    return;
  }


  gst_structure_fixate_field_nearest_int (outs, "channels", in_chans);

  if (!gst_structure_get_int (outs, "channels", &out_chans)) {

    gst_structure_remove_field (outs, "channel-positions");
    return;
  }


  out_layout = gst_structure_get_value (outs, "channel-positions");


  in_layout = gst_structure_get_value (ins, "channel-positions");

  if (out_layout == NULL) {
    if (out_chans <= 2 && (in_chans != out_chans || in_layout == NULL))
      return;
    GST_WARNING_OBJECT (base, "downstream caps contain no channel layout");
  }

  if (in_chans == out_chans && in_layout != NULL) {
    GValue res = { 0, };


    if (out_layout == NULL) {
      gst_structure_set_value (outs, "channel-positions", in_layout);
      return;
    }


    if (GST_VALUE_HOLDS_ARRAY (out_layout) &&
        gst_value_array_get_size (out_layout) == out_chans) {
      return;
    }


    if (gst_value_intersect (&res, in_layout, out_layout)) {
      gst_structure_set_value (outs, "channel-positions", in_layout);
      g_value_unset (&res);
      return;
    }


    if ((out_layout = find_suitable_channel_layout (out_layout, out_chans))) {
      gst_structure_set_value (outs, "channel-positions", out_layout);
      return;
    }


    GST_WARNING_OBJECT (base, "unexpected output channel layout");
  }


  if (out_layout != NULL && GST_VALUE_HOLDS_LIST (out_layout))
    out_layout = find_suitable_channel_layout (out_layout, out_chans);

  if (out_layout != NULL) {
    if (GST_VALUE_HOLDS_ARRAY (out_layout) &&
        gst_value_array_get_size (out_layout) == out_chans) {

      gst_structure_set_value (outs, "channel-positions", out_layout);
      return;
    }


    GST_WARNING_OBJECT (base, "invalid or unexpected channel-positions");
  }


  if (out_chans > 0 && out_chans <= G_N_ELEMENTS (default_positions[0])) {
    GST_DEBUG_OBJECT (base, "using default channel layout as fallback");
    gst_audio_set_channel_positions (outs, default_positions[out_chans - 1]);
  }
}
