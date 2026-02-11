gst_caps_normalize (GstCaps * caps)
{
  NormalizeForeach nf;
  guint i;

  g_return_val_if_fail (GST_IS_CAPS (caps), NULL);

  caps = gst_caps_make_writable (caps);
  nf.caps = caps;

  for (i = 0; i < gst_caps_get_size (nf.caps); i++) {
    nf.structure = gst_caps_get_structure_unchecked (nf.caps, i);
    nf.features = gst_caps_get_features_unchecked (nf.caps, i);
    while (!gst_structure_foreach (nf.structure,
            gst_caps_normalize_foreach, &nf));
  }

  return nf.caps;
}
