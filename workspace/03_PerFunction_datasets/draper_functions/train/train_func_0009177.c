evd_tls_privkey_import_from_file_thread (GSimpleAsyncResult *res,
                                         GObject            *object,
                                         GCancellable       *cancellable)
{
  EvdTlsPrivkey *self = EVD_TLS_PRIVKEY (object);
  gchar *filename;
  gchar *content;
  gsize size;
  GError *error = NULL;

  filename = g_simple_async_result_get_op_res_gpointer (res);

  if (! g_file_get_contents (filename, &content, &size, &error) ||
      ! evd_tls_privkey_import (self, content, size, &error))
    {
      g_simple_async_result_set_from_error (res, error);
      g_error_free (error);
    }

  g_free (content);
  g_free (filename);
  g_object_unref (res);
}
