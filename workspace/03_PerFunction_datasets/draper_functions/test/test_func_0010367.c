utils_append_value_helper_pair (DBusMessageIter  *main_iter,
				const GConfValue *value)
{
  DBusMessageIter  struct_iter;
  GConfValue      *car, *cdr;
  gint32           type;

  d(g_print ("Append value (pair)\n"));

  g_assert (value->type == GCONF_VALUE_PAIR);

  dbus_message_iter_open_container (main_iter,
				    DBUS_TYPE_STRUCT,
				    NULL,
				    &struct_iter);

  car = gconf_value_get_car (value);
  cdr = gconf_value_get_cdr (value);


  if (car)
    type = car->type;
  else
    type = GCONF_VALUE_INVALID;
  dbus_message_iter_append_basic (&struct_iter, DBUS_TYPE_INT32, &type);

  if (cdr)
    type = cdr->type;
  else
    type = GCONF_VALUE_INVALID;
  dbus_message_iter_append_basic (&struct_iter, DBUS_TYPE_INT32, &type);


  if (car)
    utils_append_value_helper_fundamental (&struct_iter, car);

  if (cdr)
    utils_append_value_helper_fundamental (&struct_iter, cdr);

  dbus_message_iter_close_container (main_iter, &struct_iter);
}
