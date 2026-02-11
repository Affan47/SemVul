rtp_source_has_retained (RTPSource * src, GCompareFunc func, gconstpointer data)
{
  if (g_queue_find_custom (src->retained_feedback, data, func))
    return TRUE;
  else
    return FALSE;
}
