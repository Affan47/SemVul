gst_encode_bin_setup_profile (GstEncodeBin * ebin, GstEncodingProfile * profile)
{
  gboolean res;

  g_return_val_if_fail (ebin->profile == NULL, FALSE);

  GST_DEBUG ("Setting up profile %s (type:%s)",
      gst_encoding_profile_get_name (profile),
      gst_encoding_profile_get_type_nick (profile));

  ebin->profile = profile;
  gst_mini_object_ref ((GstMiniObject *) ebin->profile);


  res = create_elements_and_pads (ebin);
  if (res == FALSE)
    gst_encode_bin_tear_down_profile (ebin);

  return res;
}
