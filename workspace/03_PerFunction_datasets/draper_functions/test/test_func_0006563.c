added_to_group_cb                       (GObject      *object,
                                         GAsyncResult *res,
                                         gpointer      user_data)
{
  FspSession *session = FSP_SESSION (object);
  GError *error = NULL;
  gboolean result = FALSE;

  result = fsp_session_add_to_group_finish (session, res, &error);
  if (error != NULL)
    {
      g_print ("Error creating group: %s\n", error->message);
      g_error_free (error);
    }
  else
    {
      g_print ("[added_to_groups_cb]::Success! (%s)\n\n",
               result ? "OK" : "FAIL");
    }
}
