probe_setting (GstUvcH264Src * self, uvcx_control_selector_t selector,
    guint offset, gint size, gpointer min, gpointer def, gpointer max)
{
  guchar *min_p, *def_p, *max_p;
  gboolean ret = FALSE;
  __u16 len;

  if (!xu_query (self, selector, UVC_GET_LEN, (guchar *) & len)) {
    GST_WARNING_OBJECT (self, "probe_setting GET_LEN error");
    return FALSE;
  }
  min_p = g_malloc0 (len);
  def_p = g_malloc0 (len);
  max_p = g_malloc0 (len);

  if (!xu_query (self, selector, UVC_GET_MIN, min_p)) {
    GST_WARNING_OBJECT (self, "probe_setting GET_MIN error");
    goto end;
  }
  if (!xu_query (self, selector, UVC_GET_DEF, def_p)) {
    GST_WARNING_OBJECT (self, "probe_setting GET_DEF error");
    goto end;
  }
  if (!xu_query (self, selector, UVC_GET_MAX, max_p)) {
    GST_WARNING_OBJECT (self, "probe_setting GET_MAX error");
    goto end;
  }

  switch (size) {
    case -1:
      STORE_MIN_DEF_MAX (gint8);
      ret = TRUE;
      break;
    case 1:
      STORE_MIN_DEF_MAX (guint8);
      ret = TRUE;
      break;
    case -2:
      STORE_MIN_DEF_MAX (gint16);
      ret = TRUE;
      break;
    case 2:
      STORE_MIN_DEF_MAX (guint16);
      ret = TRUE;
      break;
    case -4:
      STORE_MIN_DEF_MAX (gint32);
      ret = TRUE;
      break;
    case 4:
      STORE_MIN_DEF_MAX (guint32);
      ret = TRUE;
      break;
    default:
      break;
  }

end:
  g_free (min_p);
  g_free (def_p);
  g_free (max_p);

  return ret;
}
