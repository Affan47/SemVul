gst_dfbvideosink_getcaps (GstBaseSink * bsink)
{
  GstDfbVideoSink *dfbvideosink;
  GstCaps *caps = NULL;
  gint i;

  dfbvideosink = GST_DFBVIDEOSINK (bsink);

  if (!dfbvideosink->setup) {
    caps = gst_caps_copy (gst_pad_get_pad_template_caps (GST_VIDEO_SINK_PAD
            (dfbvideosink)));
    GST_DEBUG_OBJECT (dfbvideosink, "getcaps called and we are not setup yet, "
        "returning template %" GST_PTR_FORMAT, caps);
    goto beach;
  } else {
    GST_DEBUG_OBJECT (dfbvideosink, "getcaps called, checking our internal "
        "format");
    if (dfbvideosink->ext_surface) {


      caps = gst_dfbvideosink_get_caps_from_format (dfbvideosink->pixel_format);
    } else {

      gboolean accelerated = TRUE;
      caps = gst_caps_new_empty ();

      do {
        if (gst_dfbvideosink_can_blit_from_format (dfbvideosink, DSPF_RGB16,
                accelerated)) {
          gst_caps_append (caps,
              gst_dfbvideosink_get_caps_from_format (DSPF_RGB16));
        }
        if (gst_dfbvideosink_can_blit_from_format (dfbvideosink, DSPF_RGB24,
                accelerated)) {
          gst_caps_append (caps,
              gst_dfbvideosink_get_caps_from_format (DSPF_RGB24));
        }
        if (gst_dfbvideosink_can_blit_from_format (dfbvideosink, DSPF_RGB32,
                accelerated)) {
          gst_caps_append (caps,
              gst_dfbvideosink_get_caps_from_format (DSPF_RGB32));
        }
        if (gst_dfbvideosink_can_blit_from_format (dfbvideosink, DSPF_ARGB,
                accelerated)) {
          gst_caps_append (caps,
              gst_dfbvideosink_get_caps_from_format (DSPF_ARGB));
        }
        if (gst_dfbvideosink_can_blit_from_format (dfbvideosink, DSPF_YUY2,
                accelerated)) {
          gst_caps_append (caps,
              gst_dfbvideosink_get_caps_from_format (DSPF_YUY2));
        }
        if (gst_dfbvideosink_can_blit_from_format (dfbvideosink, DSPF_UYVY,
                accelerated)) {
          gst_caps_append (caps,
              gst_dfbvideosink_get_caps_from_format (DSPF_UYVY));
        }
        if (gst_dfbvideosink_can_blit_from_format (dfbvideosink, DSPF_I420,
                accelerated)) {
          gst_caps_append (caps,
              gst_dfbvideosink_get_caps_from_format (DSPF_I420));
        }
        if (gst_dfbvideosink_can_blit_from_format (dfbvideosink, DSPF_YV12,
                accelerated)) {
          gst_caps_append (caps,
              gst_dfbvideosink_get_caps_from_format (DSPF_YV12));
        }
        accelerated = !accelerated;
      } while (accelerated == FALSE);
    }
  }

  for (i = 0; i < gst_caps_get_size (caps); i++) {
    GstStructure *structure = gst_caps_get_structure (caps, i);

    gst_structure_set (structure,
        "width", GST_TYPE_INT_RANGE, 1, G_MAXINT,
        "height", GST_TYPE_INT_RANGE, 1, G_MAXINT,
        "framerate", GST_TYPE_FRACTION_RANGE, 0, 1, G_MAXINT, 1, NULL);

    if (!dfbvideosink->hw_scaling && dfbvideosink->par) {
      int nom, den;

      nom = gst_value_get_fraction_numerator (dfbvideosink->par);
      den = gst_value_get_fraction_denominator (dfbvideosink->par);
      gst_structure_set (structure, "pixel-aspect-ratio",
          GST_TYPE_FRACTION, nom, den, NULL);
    }
  }

  GST_DEBUG_OBJECT (dfbvideosink, "returning our caps %" GST_PTR_FORMAT, caps);

beach:
  return caps;
}
