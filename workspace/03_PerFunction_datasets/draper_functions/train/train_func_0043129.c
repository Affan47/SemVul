upload_cb                               (GObject      *object,
                                         GAsyncResult *res,
                                         gpointer      source_func)
{
  FspSession *session = FSP_SESSION (object);
  GError *error = NULL;

  g_free (uploaded_photo_id);
  uploaded_photo_id = fsp_session_upload_finish (session, res, &error);

  if (error != NULL)
    {
      g_print ("Error uploading picture: %s\n", error->message);
      g_error_free (error);
    }
  else
    {
      g_print ("[upload_cb]::Success! Photo ID: %s\n\n", uploaded_photo_id);


      g_print ("Press ENTER to continue...\n\n");
      getchar ();

      if (source_func == get_tags_list_cb)
        {

          g_print ("Setting license for photo %s...\n", uploaded_photo_id);
          fsp_session_set_license (session, uploaded_photo_id,
                                   FSP_LICENSE_AT_NC_ND, NULL,
                                   set_license_cb, NULL);
        }
      else if (source_func == photoset_created_cb)
        {

          g_print ("Adding picture to photoset...\n");
          fsp_session_add_to_photoset (session,
                                       uploaded_photo_id,
                                       created_photoset_id,
                                       NULL, added_to_photoset_cb, NULL);
        }
      else if (source_func == get_groups_cb)
        {

          g_print ("Adding picture to group...\n");
          fsp_session_add_to_group (session,
                                    uploaded_photo_id,
                                    first_group_id,
                                    NULL, added_to_group_cb, NULL);
        }
    }
}
