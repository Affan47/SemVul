get_string_property(DBusGProxy *proxy, const char * property, std::string & value)
{
  char* c_value = NULL;
  GError *error = NULL;

  dbus_g_proxy_call (proxy, "GetPropertyString", &error, G_TYPE_STRING, property, G_TYPE_INVALID, G_TYPE_STRING, &c_value, G_TYPE_INVALID);

  if (error != NULL)
    g_error_free(error);
   else
     if (c_value)
       value = c_value;

  g_free (c_value);
}
