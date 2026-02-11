gst_raw_parse_set_src_caps (GstRawParse * rp)
{
  GstRawParseClass *rp_class = GST_RAW_PARSE_GET_CLASS (rp);
  GstCaps *caps;

  if (rp->negotiated)
    return TRUE;

  if (rp_class->get_caps) {
    caps = rp_class->get_caps (rp);
  } else {
    GST_WARNING
        ("Subclass doesn't implement get_caps() method, using ANY caps");
    caps = gst_caps_new_any ();
  }

  rp->negotiated = gst_pad_set_caps (rp->srcpad, caps);

  return rp->negotiated;
}
