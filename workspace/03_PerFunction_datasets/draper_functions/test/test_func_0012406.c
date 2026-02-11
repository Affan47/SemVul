photoset_created_cb                     (GObject      *object,
                                         GAsyncResult *res,
                                         gpointer      user_data)
{
  FspSession *session = FSP_SESSION (object);
  GError *error = NULL;
  created_photoset_id =
    fsp_session_create_photoset_finish (session, res, &error);

  if (error != NULL)
    {
      g_print ("Error creating photoset: %s\n", error->message);
      g_error_free (error);
    }
  else
    {
      g_print ("[photosets_created_cb]::Success! Photo set Id: %s\n\n",
               created_photoset_id);

      getchar ();


      g_print ("Uploading a new picture to be added to the photoset...");
      fsp_session_upload (session,
                          test_photo_path,
                          "Yet another title",
                          "Yet another description ",
                          "yet some other tags",
                          FSP_VISIBILITY_NO,
                          FSP_VISIBILITY_YES,
                          FSP_VISIBILITY_NONE,
                          FSP_SAFETY_LEVEL_NONE,
                          FSP_CONTENT_TYPE_PHOTO,
                          FSP_SEARCH_SCOPE_NONE,
                          NULL, upload_cb,
                          (gpointer) photoset_created_cb);
    }
}
