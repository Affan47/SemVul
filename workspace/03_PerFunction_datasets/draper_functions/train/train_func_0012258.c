gst_jpegenc_getcaps (GstPad * pad)
{
  GstJpegEnc *jpegenc = GST_JPEGENC (gst_pad_get_parent (pad));
  GstCaps *caps, *othercaps;
  const GstCaps *templ;
  gint i, j;
  GstStructure *structure = NULL;


  othercaps = gst_pad_peer_get_caps_reffed (jpegenc->srcpad);
  if (othercaps == NULL ||
      gst_caps_is_empty (othercaps) || gst_caps_is_any (othercaps)) {
    caps = gst_caps_copy (gst_pad_get_pad_template_caps (pad));
    goto done;
  }

  caps = gst_caps_new_empty ();
  templ = gst_pad_get_pad_template_caps (pad);

  for (i = 0; i < gst_caps_get_size (templ); i++) {

    for (j = 0; j < gst_caps_get_size (othercaps); j++) {
      GstStructure *s = gst_caps_get_structure (othercaps, j);
      const GValue *val;

      structure = gst_structure_copy (gst_caps_get_structure (templ, i));
      if ((val = gst_structure_get_value (s, "width")))
        gst_structure_set_value (structure, "width", val);
      if ((val = gst_structure_get_value (s, "height")))
        gst_structure_set_value (structure, "height", val);
      if ((val = gst_structure_get_value (s, "framerate")))
        gst_structure_set_value (structure, "framerate", val);

      gst_caps_merge_structure (caps, structure);
    }
  }

done:

  gst_caps_replace (&othercaps, NULL);
  gst_object_unref (jpegenc);

  return caps;
}
