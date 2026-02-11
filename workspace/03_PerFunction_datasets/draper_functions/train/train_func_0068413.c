initialize_role_names ()
{
  GTypeClass *enum_class;
  GEnumValue *enum_value;
  int i;
  gchar *role_name = NULL;

  if (role_names)
    return;

  role_names = g_ptr_array_new ();
  enum_class = g_type_class_ref (ATK_TYPE_ROLE);
  if (!G_IS_ENUM_CLASS(enum_class))
    return;

  for (i = 0; i < ATK_ROLE_LAST_DEFINED; i++)
    {
      enum_value = g_enum_get_value (G_ENUM_CLASS (enum_class), i);
      role_name = g_strdup (enum_value->value_nick);

      compact_role_name (role_name);
      g_ptr_array_add (role_names, role_name);
    }

  g_type_class_unref (enum_class);

}
