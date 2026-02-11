grl_source_store_sync (GrlSource *source,
                       GrlMediaBox *parent,
                       GrlMedia *media,
                       GrlWriteFlags flags,
                       GError **error)
{
  GrlDataSync *ds;

  ds = g_slice_new0 (GrlDataSync);

  if (grl_source_store_impl (source,
                             parent,
                             media,
                             flags,
                             store_result_async_cb,
                             ds))
    grl_wait_for_async_operation_complete (ds);

  if (ds->error) {
    if (error) {
      *error = ds->error;
    } else {
      g_error_free (ds->error);
    }
  }

  g_slice_free (GrlDataSync, ds);
}
