atk_state_type_get_name (AtkStateType type)
{
  GTypeClass *type_class;
  GEnumValue *value;
  const gchar *name = NULL;

  type_class = g_type_class_ref (ATK_TYPE_STATE_TYPE);
  g_return_val_if_fail (G_IS_ENUM_CLASS (type_class), NULL);

  value = g_enum_get_value (G_ENUM_CLASS (type_class), type);

  if (value)
    {
      name = value->value_nick;
    }
  else
    {
      if (type <= last_type)
        {
          if (type >= 0)
            name = state_names[type];
        }
    }

  return name;
}
