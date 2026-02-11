gst_object_default_deep_notify (GObject * object, GstObject * orig,
    GParamSpec * pspec, gchar ** excluded_props)
{
  GValue value = { 0, };
  gchar *str = NULL;
  gchar *name = NULL;

  if (pspec->flags & G_PARAM_READABLE) {

    while (excluded_props != NULL && *excluded_props != NULL) {
      if (strcmp (pspec->name, *excluded_props) == 0)
        return;
      excluded_props++;
    }
    g_value_init (&value, pspec->value_type);
    g_object_get_property (G_OBJECT (orig), pspec->name, &value);

    if (G_VALUE_HOLDS_STRING (&value))
      str = g_value_dup_string (&value);
    else
      str = gst_value_serialize (&value);
    name = gst_object_get_path_string (orig);
    g_print ("%s: %s = %s\n", name, pspec->name, str);
    g_free (name);
    g_free (str);
    g_value_unset (&value);
  } else {
    name = gst_object_get_path_string (orig);
    g_warning ("Parameter %s not readable in %s.", pspec->name, name);
    g_free (name);
  }
}
