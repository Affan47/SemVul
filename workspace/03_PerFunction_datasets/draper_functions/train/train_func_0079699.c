read_dbus_string_dict_value (GVariant *args, const gchar *key)
{
  GVariant *a;
  GVariantIter iter;
  const gchar *str, *val;
  gchar *res;

  if (! g_variant_is_of_type (args, G_VARIANT_TYPE ("(a{ss})")))
    return NULL;

  g_variant_get (args, "(@a{ss})", &a);

  res = NULL;
  g_variant_iter_init (&iter, a);
  while (g_variant_iter_next (&iter, "{&s&s}", &str, &val))
    {
      if (g_strcmp0 (str, key) == 0)
        {
          res = g_strdup (val);
          break;
        }
    }

  g_variant_unref (a);

  return res;
}
