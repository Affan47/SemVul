_update_status_cb (DBusGProxy *proxy,
                   GError     *error,
                   gpointer    userdata)
{
  SwClientServiceCallClosure *closure = (SwClientServiceCallClosure *)userdata;
  SwClientServiceUpdateStatusCallback cb;

  if (error)
  {
    g_warning (G_STRLOC ": Error updating status: %s",
               error->message);
  }

  cb = (SwClientServiceUpdateStatusCallback)closure->cb;
  cb (closure->service,
      error,
      closure->userdata);

  if (error)
    g_error_free (error);

  g_object_unref (closure->service);
  g_slice_free (SwClientServiceCallClosure, closure);
}
