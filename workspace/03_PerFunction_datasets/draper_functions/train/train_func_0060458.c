gst_audio_convert_fixate_caps (GstBaseTransform * base,
    GstPadDirection direction, GstCaps * caps, GstCaps * othercaps)
{
  GstStructure *ins, *outs;
  GstCaps *result;

  GST_DEBUG_OBJECT (base, "trying to fixate othercaps %" GST_PTR_FORMAT
      " based on caps %" GST_PTR_FORMAT, othercaps, caps);

  result = gst_caps_intersect (othercaps, caps);
  if (gst_caps_is_empty (result)) {
    GstCaps *removed;

    if (result)
      gst_caps_unref (result);

    removed = gst_audio_convert_caps_remove_format_info (caps, FALSE);
    result = gst_caps_intersect (othercaps, removed);
    gst_caps_unref (removed);
    if (gst_caps_is_empty (result)) {
      if (result)
        gst_caps_unref (result);
      result = othercaps;
    } else {
      gst_caps_unref (othercaps);
    }
  } else {
    gst_caps_unref (othercaps);
  }

  GST_DEBUG_OBJECT (base, "now fixating %" GST_PTR_FORMAT, result);


  result = gst_caps_make_writable (result);

  ins = gst_caps_get_structure (caps, 0);
  outs = gst_caps_get_structure (result, 0);

  gst_audio_convert_fixate_channels (base, ins, outs);
  gst_audio_convert_fixate_format (base, ins, outs);


  result = gst_caps_fixate (result);

  GST_DEBUG_OBJECT (base, "fixated othercaps to %" GST_PTR_FORMAT, result);

  return result;
}
