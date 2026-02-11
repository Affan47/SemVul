check_guint_arg (GObject *object,
		 const gchar *name,
		 guint *value_return)
{
  GParamSpec *pspec;

  g_return_val_if_fail (object != NULL, FALSE);

  pspec = g_object_class_find_property (G_OBJECT_GET_CLASS (object), name);
  if (pspec != NULL) {
    GValue value = { 0, };

    g_value_init (&value, G_TYPE_UINT);
    g_object_get_property (G_OBJECT (object), name, &value);
    *value_return = g_value_get_uint (&value);
    g_value_unset (&value);

    return TRUE;
  } else
    return FALSE;
}
