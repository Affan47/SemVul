atspi_component_get_accessible_at_point (AtspiComponent *obj,
                                          gint x,
                                          gint y,
                                          AtspiCoordType ctype, GError **error)
{
  dbus_int32_t d_x = x, d_y = y;
  dbus_uint32_t d_ctype = ctype;
  DBusMessage *reply;

  g_return_val_if_fail (obj != NULL, FALSE);

  reply = _atspi_dbus_call_partial (obj, atspi_interface_component, "GetAccessibleAtPoint", error, "iiu", d_x, d_y, d_ctype);

  return _atspi_dbus_return_accessible_from_message (reply);
}
