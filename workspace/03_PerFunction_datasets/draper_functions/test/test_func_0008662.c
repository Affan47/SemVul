find_transport (GstRTSPMediaStream * stream, const gchar * rtcp_from)
{
  GList *walk;
  GstRTSPMediaTrans *result = NULL;
  const gchar *tmp;
  gchar *dest;
  guint port;

  if (rtcp_from == NULL)
    return NULL;

  tmp = g_strrstr (rtcp_from, ":");
  if (tmp == NULL)
    return NULL;

  port = atoi (tmp + 1);
  dest = g_strndup (rtcp_from, tmp - rtcp_from);

  GST_INFO ("finding %s:%d", dest, port);

  for (walk = stream->transports; walk; walk = g_list_next (walk)) {
    GstRTSPMediaTrans *trans = walk->data;
    gint min, max;

    min = trans->transport->client_port.min;
    max = trans->transport->client_port.max;

    if ((strcmp (trans->transport->destination, dest) == 0) && (min == port
            || max == port)) {
      result = trans;
      break;
    }
  }
  g_free (dest);

  return result;
}
