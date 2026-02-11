gst_gio_error (gpointer element, const gchar * func_name, GError ** err,
    GstFlowReturn * ret)
{
  gboolean handled = TRUE;

  if (ret)
    *ret = GST_FLOW_ERROR;

  if (GST_GIO_ERROR_MATCHES (*err, CANCELLED)) {
    GST_DEBUG_OBJECT (element, "blocking I/O call cancelled (%s)", func_name);
    if (ret)
      *ret = GST_FLOW_WRONG_STATE;
  } else if (*err != NULL) {
    handled = FALSE;
  } else {
    GST_ELEMENT_ERROR (element, LIBRARY, FAILED, (NULL),
        ("%s call failed without error set", func_name));
  }

  if (handled)
    g_clear_error (err);

  return handled;
}
