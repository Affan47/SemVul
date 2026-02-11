_dbus_gvalue_demarshal_message  (DBusGValueMarshalCtx    *context,
				DBusMessage             *message,
				guint                    n_types,
				const GType             *types,
				GError                 **error)
{
  GValueArray *ret;
  DBusMessageIter iter;
  int current_type;
  guint index_;

  ret = g_value_array_new (6);

  dbus_message_iter_init (message, &iter);
  index_ = 0;
  while ((current_type = dbus_message_iter_get_arg_type (&iter)) != DBUS_TYPE_INVALID)
    {
      GValue *value;
      GType gtype;

      if (index_ >= n_types)
	{
	  g_set_error (error, DBUS_GERROR,
		       DBUS_GERROR_INVALID_ARGS,
		       "Too many arguments in message");
	  goto lose;
	}

      g_value_array_append (ret, NULL);
      value = g_value_array_get_nth (ret, index_);

      gtype = types[index_];
      g_value_init (value, gtype);

      if (!_dbus_gvalue_demarshal (context, &iter, value, error))
	goto lose;
      dbus_message_iter_next (&iter);
      index_++;
    }
  if (index_ < n_types)
    {
      g_set_error (error, DBUS_GERROR,
		   DBUS_GERROR_INVALID_ARGS,
		   "Too few arguments in message");
      goto lose;
    }

  return ret;
 lose:
  g_value_array_free (ret);
  return NULL;
}
