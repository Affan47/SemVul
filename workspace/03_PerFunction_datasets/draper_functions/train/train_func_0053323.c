remove_udp_destination (GstRTSPMedia * media, GstRTSPMediaStream * stream,
    gchar * dest, gint min, gint max)
{
  gboolean do_remove = TRUE;
  RTSPDestination *ndest = NULL;
  GList *find = NULL;

  if (stream->filter_duplicates) {
    RTSPDestination fdest;

    fdest.dest = dest;
    fdest.min = min;
    fdest.max = max;


    find =
        g_list_find_custom (stream->destinations, &fdest,
        (GCompareFunc) dest_compare);
    if (!find)
      return;

    ndest = (RTSPDestination *) find->data;
    if (--ndest->count > 0) {
      do_remove = FALSE;
      GST_INFO ("still streaming to %s:%d-%d with %d clients", dest, min, max,
          ndest->count);
    }
  }

  if (do_remove) {
    GST_INFO ("removing %s:%d-%d", dest, min, max);
    g_signal_emit_by_name (stream->udpsink[0], "remove", dest, min, NULL);
    g_signal_emit_by_name (stream->udpsink[1], "remove", dest, max, NULL);

    if (stream->filter_duplicates) {
      stream->destinations = g_list_delete_link (stream->destinations, find);
      free_destination (ndest);
    }
  }
}
