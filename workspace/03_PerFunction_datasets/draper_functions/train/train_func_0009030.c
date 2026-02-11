sync_idle_cb (gpointer data)
{
  GConfClient *conf;
  GConfChangeSet *changeset;
  GError *error = NULL;

  _terminal_debug_print (TERMINAL_DEBUG_ACCELS,
                         "gconf sync handler\n");

  sync_idle_id = 0;

  conf = gconf_client_get_default ();

  changeset = gconf_change_set_new ();
  g_hash_table_foreach (gconf_key_to_entry, (GHFunc) add_key_entry_to_changeset, changeset);
  if (!gconf_client_commit_change_set (conf, changeset, TRUE, &error))
    {
      g_printerr ("Error committing the accelerator changeset: %s\n", error->message);
      g_error_free (error);
    }

  gconf_change_set_unref (changeset);
  g_object_unref (conf);

  return FALSE;
}
