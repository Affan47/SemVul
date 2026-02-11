gst_ogg_stream_get_media_type (GstOggStream * pad)
{
  const GstCaps *caps = pad->caps;
  const GstStructure *structure;
  if (!caps)
    return NULL;
  structure = gst_caps_get_structure (caps, 0);
  if (!structure)
    return NULL;
  return gst_structure_get_name (structure);
}
