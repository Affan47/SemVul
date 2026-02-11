get_aggregate_control (GstRTSPSrc * src)
{
  const gchar *base;

  if (src->control)
    base = src->control;
  else if (src->content_base)
    base = src->content_base;
  else if (src->conninfo.url_str)
    base = src->conninfo.url_str;
  else
    base = "/";

  return base;
}
