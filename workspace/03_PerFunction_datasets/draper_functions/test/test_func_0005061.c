atspi_editable_text_insert_text (AtspiEditableText *obj,
                                 gint position,
                                 const gchar *text,
                                 gint length,
                                 GError **error)
{
  dbus_int32_t d_position = position, d_length = length;
  dbus_bool_t retval = FALSE;

  g_return_val_if_fail (obj != NULL, FALSE);

  _atspi_dbus_call (obj, atspi_interface_editable_text, "InsertText", error, "isi=>b", d_position, text, d_length, &retval);

  return retval;
}
