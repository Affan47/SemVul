gst_discoverer_info_get_streams (GstDiscovererInfo * info, GType streamtype)
{
  GList *tmp, *res = NULL;

  for (tmp = info->stream_list; tmp; tmp = tmp->next) {
    GstDiscovererStreamInfo *stmp = (GstDiscovererStreamInfo *) tmp->data;

    if (G_TYPE_CHECK_INSTANCE_TYPE (stmp, streamtype))
      res = g_list_append (res, gst_discoverer_stream_info_ref (stmp));
  }

  return res;
}
