changed_check_cb (GObject       *source_object,
                  GAsyncResult  *res,
                  gpointer       user_data)
{
  PolkitPermission *permission = POLKIT_PERMISSION (user_data);
  PolkitAuthorizationResult *result;
  GError *error;

  error = NULL;
  result = polkit_authority_check_authorization_finish (permission->authority,
                                                        res,
                                                        &error);
  if (result != NULL)
    {
      process_result (permission, result);
    }
  else
    {


      g_warning ("Error checking authorization for action id %s: %s",
                 permission->action_id,
                 error->message);
      g_error_free (error);
    }
  g_object_unref (permission);
}
