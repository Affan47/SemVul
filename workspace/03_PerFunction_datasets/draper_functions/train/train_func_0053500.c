adpcmenc_sink_setcaps (GstPad * pad, GstCaps * caps)
{
  ADPCMEnc *enc = (ADPCMEnc *) gst_pad_get_parent (pad);
  GstStructure *structure = gst_caps_get_structure (caps, 0);

  if (!gst_structure_get_int (structure, "rate", &enc->rate))
    return FALSE;
  if (!gst_structure_get_int (structure, "channels", &enc->channels))
    return FALSE;

  if (enc->is_setup) {
    adpcmenc_teardown (enc);
  }
  adpcmenc_setup (enc);

  gst_object_unref (enc);

  return TRUE;
}
