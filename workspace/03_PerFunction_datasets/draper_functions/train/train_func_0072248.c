favourite_contacts_file_open_cb (GObject *object,
    GAsyncResult *result,
    gpointer user_data)
{
  GFile *file = G_FILE (object);
  TplActionChain *action_chain = (TplActionChain *) user_data;
  GFileInputStream *stream;
  GError *error = NULL;

  if ((stream = g_file_read_finish (file, result, &error)))
    {
      GDataInputStream *data_stream = g_data_input_stream_new (
          G_INPUT_STREAM (stream));

      g_data_input_stream_read_line_async (data_stream, G_PRIORITY_DEFAULT,
          NULL, favourite_contacts_file_read_line_cb, action_chain);

      g_object_unref (stream);
    }
  else if (error->code == G_IO_ERROR_NOT_FOUND)
    {
      DEBUG ("Favourite contacts file doesn't exist yet. Will create as "
          "necessary.");

      g_clear_error (&error);
      _tpl_action_chain_continue (action_chain);
    }
  else
    {
      g_prefix_error (&error, "Failed to open the favourite contacts file: ");
      _tpl_action_chain_terminate (action_chain, error);
      g_clear_error (&error);
    }
}
