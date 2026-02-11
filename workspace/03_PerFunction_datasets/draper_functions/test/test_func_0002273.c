ensure_handle_cb (GObject *source,
    GAsyncResult *result,
    gpointer user_data)
{
  TpHandleRepoIface *repo = (TpHandleRepoIface *) source;
  EnsureHandleData *data = user_data;
  RequestHandlesData *request = data->request;
  TpHandle handle;
  GError *error = NULL;


  if (request->context == NULL)
    goto out;

  handle = tp_handle_ensure_finish (repo, result, &error);
  if (handle == 0)
    {
      dbus_g_method_return_error (request->context, error);
      request->context = NULL;
      g_clear_error (&error);
    }
  else
    {
      TpHandle *handle_p;

      handle_p = &g_array_index (request->handles, TpHandle, data->pos);
      g_assert (*handle_p == 0);
      *handle_p = handle;
    }

out:
  request->n_pending--;
  if (request->n_pending == 0)
    {
      if (request->context != NULL)
        {
          tp_svc_connection_return_from_request_handles (request->context,
              request->handles);
        }
      g_array_unref (request->handles);
      g_slice_free (RequestHandlesData, request);
    }

  g_slice_free (EnsureHandleData, data);
}
