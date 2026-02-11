on_name_acquired (GDBusConnection *connection,
                  const gchar     *name,
                  gpointer         user_data)
{
  GError *error;

  skeleton = gvfs_metadata_skeleton_new ();

  g_signal_connect (skeleton, "handle-set", G_CALLBACK (handle_set), skeleton);
  g_signal_connect (skeleton, "handle-unset", G_CALLBACK (handle_unset), skeleton);
  g_signal_connect (skeleton, "handle-get", G_CALLBACK (handle_get), skeleton);
  g_signal_connect (skeleton, "handle-remove", G_CALLBACK (handle_remove), skeleton);
  g_signal_connect (skeleton, "handle-move", G_CALLBACK (handle_move), skeleton);

  error = NULL;
  if (!g_dbus_interface_skeleton_export (G_DBUS_INTERFACE_SKELETON (skeleton), connection,
                                         G_VFS_DBUS_METADATA_PATH, &error))
    {
      g_printerr ("Error exporting volume monitor: %s (%s, %d)\n",
                  error->message, g_quark_to_string (error->domain), error->code);
      g_error_free (error);
    }
}
