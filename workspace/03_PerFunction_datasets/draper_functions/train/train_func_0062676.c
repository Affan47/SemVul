on_unix_process_check_vanished_timeout (gpointer user_data)
{
  TemporaryAuthorization *authorization = user_data;
  GError *error;


  error = NULL;
  if (!polkit_subject_exists_sync (authorization->subject,
                                   NULL,
                                   &error))
    {
      if (error != NULL)
        {
          g_printerr ("Error checking if process exists: %s\n", error->message);
          g_error_free (error);
        }
      else
        {
          gchar *s;

          s = polkit_subject_to_string (authorization->subject);
          g_debug ("Removing tempoary authorization with id `%s' for action-id `%s' for subject `%s': "
                   "subject has vanished",
                   authorization->id,
                   authorization->action_id,
                   s);
          g_free (s);

          authorization->store->authorizations = g_list_remove (authorization->store->authorizations,
                                                                authorization);
          g_signal_emit_by_name (authorization->store->authority, "changed");
          temporary_authorization_free (authorization);
        }
    }


  return TRUE;
}
