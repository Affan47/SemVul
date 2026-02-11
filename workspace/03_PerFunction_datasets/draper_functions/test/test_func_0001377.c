contact_avatar_retrieved (TpConnection *connection,
    guint handle,
    const gchar *token,
    const GArray *avatar,
    const gchar *mime_type,
    gpointer user_data G_GNUC_UNUSED,
    GObject *weak_object G_GNUC_UNUSED)
{
  TpContact *self = _tp_connection_lookup_contact (connection, handle);
  gchar *filename;
  gchar *mime_filename;
  WriteAvatarData *avatar_data;

  if (self != NULL)
    {


      contact_set_avatar_token (self, token, FALSE);
    }

  if (!build_avatar_filename (connection, token, TRUE, &filename,
      &mime_filename))
    return;


  avatar_data = g_slice_new0 (WriteAvatarData);
  avatar_data->connection = g_object_ref (connection);
  g_weak_ref_set (&avatar_data->contact, self);
  avatar_data->token = g_strdup (token);
  avatar_data->file = g_file_new_for_path (filename);


  avatar_data->data = g_bytes_new (avatar->data, avatar->len);
  avatar_data->mime_file = g_file_new_for_path (mime_filename);
  avatar_data->mime_type = g_strdup (mime_type);

  g_file_replace_contents_async (avatar_data->file,
      g_bytes_get_data (avatar_data->data, NULL), avatar->len,
      NULL, FALSE, G_FILE_CREATE_PRIVATE|G_FILE_CREATE_REPLACE_DESTINATION,
      NULL, avatar_file_written, avatar_data);

  g_free (filename);
  g_free (mime_filename);
}
