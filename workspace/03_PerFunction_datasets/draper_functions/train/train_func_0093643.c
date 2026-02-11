gst_jasper_enc_set_src_caps (GstJasperEnc * enc)
{
  GstCaps *caps;
  guint32 fourcc;
  gboolean ret;
  GstCaps *peercaps;

  peercaps = gst_pad_peer_get_caps (enc->srcpad);
  if (peercaps) {
    guint i, n;

    n = gst_caps_get_size (peercaps);
    for (i = 0; i < n; i++) {
      GstStructure *s = gst_caps_get_structure (peercaps, i);
      const gchar *name = gst_structure_get_name (s);

      if (!strcmp (name, "image/x-j2c")) {
        enc->mode = GST_JP2ENC_MODE_J2C;
        break;
      } else if (!strcmp (name, "image/x-jpc")) {
        enc->mode = GST_JP2ENC_MODE_JPC;
        break;
      } else if (!strcmp (name, "image/jp2")) {
        enc->mode = GST_JP2ENC_MODE_JP2;
        break;
      }
    }
    gst_caps_unref (peercaps);
  }


  if (gst_video_format_is_rgb (enc->format)) {
    fourcc = GST_MAKE_FOURCC ('s', 'R', 'G', 'B');
  } else {
    fourcc = GST_MAKE_FOURCC ('s', 'Y', 'U', 'V');
  }

  switch (enc->mode) {
    case GST_JP2ENC_MODE_J2C:
      caps =
          gst_caps_new_simple ("image/x-j2c", "width", G_TYPE_INT, enc->width,
          "height", G_TYPE_INT, enc->height, "fourcc", GST_TYPE_FOURCC, fourcc,
          NULL);
      break;
    case GST_JP2ENC_MODE_JPC:
      caps =
          gst_caps_new_simple ("image/x-jpc", "width", G_TYPE_INT, enc->width,
          "height", G_TYPE_INT, enc->height, "fourcc", GST_TYPE_FOURCC, fourcc,
          NULL);
      break;
    case GST_JP2ENC_MODE_JP2:
      caps = gst_caps_new_simple ("image/jp2", "width", G_TYPE_INT, enc->width,
          "height", G_TYPE_INT, enc->height, "fourcc", GST_TYPE_FOURCC, fourcc,
          NULL);
      break;
    default:
      g_assert_not_reached ();
  }


  if (enc->fps_den > 0)
    gst_caps_set_simple (caps,
        "framerate", GST_TYPE_FRACTION, enc->fps_num, enc->fps_den, NULL);
  if (enc->par_den > 0)
    gst_caps_set_simple (caps,
        "pixel-aspect-ratio", GST_TYPE_FRACTION, enc->par_num, enc->par_den,
        NULL);

  ret = gst_pad_set_caps (enc->srcpad, caps);
  gst_caps_unref (caps);

  return ret;
}
