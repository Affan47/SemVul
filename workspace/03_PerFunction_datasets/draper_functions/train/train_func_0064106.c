gst_encode_bin_release_pad (GstElement * element, GstPad * pad)
{
  GstEncodeBin *ebin = (GstEncodeBin *) element;
  StreamGroup *sgroup;


  sgroup = find_stream_group_from_pad (ebin, pad);
  if (G_UNLIKELY (sgroup == NULL))
    goto no_stream_group;


  stream_group_remove (ebin, sgroup);

  return;

no_stream_group:
  {
    GST_WARNING_OBJECT (ebin, "Couldn't find corresponding StreamGroup");
    return;
  }
}
