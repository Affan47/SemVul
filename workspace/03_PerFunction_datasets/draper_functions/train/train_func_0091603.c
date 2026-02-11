gst_discoverer_info_copy (GstDiscovererInfo * ptr)
{
  GstDiscovererInfo *ret;
  GHashTable *stream_map;
  GList *tmp;

  g_return_val_if_fail (ptr != NULL, NULL);

  stream_map = g_hash_table_new (g_direct_hash, NULL);

  ret = gst_discoverer_info_new ();

  ret->uri = g_strdup (ptr->uri);
  if (ptr->stream_info) {
    ret->stream_info = gst_discoverer_info_copy_int (ptr->stream_info,
        stream_map);
  }
  ret->duration = ptr->duration;
  if (ptr->misc)
    ret->misc = gst_structure_copy (ptr->misc);


  for (tmp = ptr->stream_list; tmp; tmp = tmp->next) {
    GstDiscovererStreamInfo *old_stream = (GstDiscovererStreamInfo *) tmp->data;
    GstDiscovererStreamInfo *new_stream = g_hash_table_lookup (stream_map,
        old_stream);
    g_assert (new_stream != NULL);
    ret->stream_list = g_list_append (ret->stream_list, new_stream);
  }

  if (ptr->tags)
    ret->tags = gst_tag_list_copy (ptr->tags);

  if (ptr->toc)
    ret->toc = gst_toc_ref (ptr->toc);

  g_hash_table_destroy (stream_map);
  return ret;
}
