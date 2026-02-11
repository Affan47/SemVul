evd_dbus_agent_unown_name (GObject  *object,
                           guint     owner_id,
                           GError  **error)
{
  ObjectData *obj_data;

  g_return_val_if_fail (G_IS_OBJECT (object), FALSE);
  g_return_val_if_fail (owner_id > 0, FALSE);

  obj_data = evd_dbus_agent_get_object_data (object);
  if (obj_data == NULL)
    {
      g_set_error_literal (error,
                           G_IO_ERROR,
                           G_IO_ERROR_INVALID_ARGUMENT,
                           "Object is invalid");
      return FALSE;
    }

  g_hash_table_remove (obj_data->owned_names, &owner_id);

  return TRUE;
}
