gst_oss_src_getcaps (GstBaseSrc * bsrc, GstCaps * filter)
{
  GstOssSrc *osssrc;
  GstCaps *caps;

  osssrc = GST_OSS_SRC (bsrc);

  if (osssrc->fd == -1) {
    GST_DEBUG_OBJECT (osssrc, "device not open, using template caps");
    return NULL;
  }

  if (osssrc->probed_caps) {
    GST_LOG_OBJECT (osssrc, "Returning cached caps");
    return gst_caps_ref (osssrc->probed_caps);
  }

  caps = gst_oss_helper_probe_caps (osssrc->fd);

  if (caps) {
    osssrc->probed_caps = gst_caps_ref (caps);
  }

  GST_INFO_OBJECT (osssrc, "returning caps %" GST_PTR_FORMAT, caps);

  if (filter && caps) {
    GstCaps *intersection;

    intersection =
        gst_caps_intersect_full (filter, caps, GST_CAPS_INTERSECT_FIRST);
    gst_caps_unref (caps);
    return intersection;
  } else {
    return caps;
  }
}
