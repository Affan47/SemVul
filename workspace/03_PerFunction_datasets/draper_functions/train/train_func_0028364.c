mxf_local_tag_free (MXFLocalTag * tag)
{
  if (tag->g_slice)
    g_slice_free1 (tag->size, tag->data);
  else
    g_free (tag->data);
  g_slice_free (MXFLocalTag, tag);
}
