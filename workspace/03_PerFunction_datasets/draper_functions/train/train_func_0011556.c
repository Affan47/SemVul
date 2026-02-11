check_auth_info_cb (GObject *object, GAsyncResult *res, gpointer unused)
{
  FspSession* session = FSP_SESSION (object);
  FspDataAuthToken *auth_token = NULL;
  GError *error = NULL;

  auth_token = fsp_session_check_auth_info_finish (session, res, &error);
  if (error != NULL)
    {
      g_print ("Error checking authorization information: %s\n", error->message);
      g_error_free (error);
    }
  else
    {
      g_print ("[check_auth_info_cb]::Result: Success!\n\n");

      g_print ("[check_auth_info_cb]::Auth token\n");
      g_print ("[check_auth_info_cb]::\ttoken = %s\n", auth_token->token);
      g_print ("[check_auth_info_cb]::\tpermissions = %s\n", auth_token->permissions);
      g_print ("[check_auth_info_cb]::\tnsid = %s\n", auth_token->nsid);
      g_print ("[check_auth_info_cb]::\tusername = %s\n", auth_token->username);
      g_print ("[check_auth_info_cb]::\tfullname = %s\n", auth_token->fullname);


      g_print ("Press ENTER to continue...\n\n");
      getchar ();


      g_print ("Retrieving upload status...\n");
      fsp_session_get_upload_status (session, NULL, get_upload_status_cb, NULL);

      fsp_data_free (FSP_DATA (auth_token));
    }
}
