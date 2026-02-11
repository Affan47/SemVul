gst_alaw_enc_getcaps (GstPad * pad)
{
  GstALawEnc *alawenc;
  GstPad *otherpad;
  GstCaps *othercaps, *result;
  const GstCaps *templ;
  const gchar *name;
  gint i;

  alawenc = GST_ALAW_ENC (GST_PAD_PARENT (pad));


  if (pad == alawenc->srcpad) {
    name = "audio/x-alaw";
    otherpad = alawenc->sinkpad;
  } else {
    name = "audio/x-raw-int";
    otherpad = alawenc->srcpad;
  }

  othercaps = gst_pad_peer_get_caps (otherpad);


  templ = gst_pad_get_pad_template_caps (pad);

  if (othercaps) {

    othercaps = gst_caps_make_writable (othercaps);


    for (i = 0; i < gst_caps_get_size (othercaps); i++) {
      GstStructure *structure;

      structure = gst_caps_get_structure (othercaps, i);


      gst_structure_set_name (structure, name);

      if (pad == alawenc->srcpad) {

        gst_structure_remove_fields (structure, "width", "depth", "endianness",
            "signed", NULL);
      } else {

        gst_structure_set (structure, "width", G_TYPE_INT, 16,
            "depth", G_TYPE_INT, 16,
            "endianness", G_TYPE_INT, G_BYTE_ORDER,
            "signed", G_TYPE_BOOLEAN, TRUE, NULL);
      }
    }

    result = gst_caps_intersect (othercaps, templ);
    gst_caps_unref (othercaps);
  } else {

    result = gst_caps_copy (templ);
  }

  return result;
}
