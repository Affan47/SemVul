_load_file_contents_cb                  (GObject      *object,
                                         GAsyncResult *res,
                                         gpointer      data)
{
  UploadPhotoData *up_clos = NULL;
  AsyncRequestData *ard_clos = NULL;
  GHashTable *extra_params = NULL;
  GFile *file = NULL;
  GError *error = NULL;
  gchar *contents = NULL;
  gsize length;

  g_return_if_fail (G_IS_FILE (object));
  g_return_if_fail (G_IS_ASYNC_RESULT (res));
  g_return_if_fail (data != NULL);


  up_clos = (UploadPhotoData *) data;
  ard_clos = up_clos->ar_data;
  extra_params = up_clos->extra_params;
  g_slice_free (UploadPhotoData, up_clos);

  file = G_FILE (object);
  if (g_file_load_contents_finish (file, res, &contents, &length, NULL, &error))
    {
      FspSession *self = NULL;
      SoupSession *soup_session = NULL;
      SoupMessage *msg = NULL;

      self = FSP_SESSION (ard_clos->object);
      msg = _get_soup_message_for_upload (file, contents, length, extra_params);
      ard_clos->soup_message = msg;

      soup_session = _get_soup_session (self);


      if (ard_clos->cancellable)
        {
          ard_clos->cancellable_id =
            g_cancellable_connect (ard_clos->cancellable,
                                   G_CALLBACK (_soup_session_cancelled_cb),
                                   ard_clos,
                                   NULL);
        }


      g_signal_connect (G_OBJECT (msg), "wrote-body-data",
                        G_CALLBACK (_wrote_body_data_cb),
                        ard_clos);


      soup_session_queue_message (soup_session, msg,
                                  _photo_upload_soup_session_cb, ard_clos);

      DEBUG ("\nRequested URL:\n%s\n", FLICKR_API_UPLOAD_URL);


      g_hash_table_unref (extra_params);
      g_object_unref (file);
    }
  else
    {

      g_warning ("Unable to get contents for file\n");
      if (error)
        g_error_free (error);
      error = g_error_new (FSP_ERROR, FSP_ERROR_OTHER, "Error reading file for upload");
      _build_async_result_and_complete (ard_clos, NULL, error);
    }
  g_free (contents);
}
