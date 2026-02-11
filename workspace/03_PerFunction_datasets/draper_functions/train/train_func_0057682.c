glade_displayable_value_is_disabled (GType type, const gchar *value)
{
  ValueTab *tab;

  g_return_val_if_fail (value && value[0], FALSE);

  if ((tab = get_value_tab (type, value, (GCompareFunc) find_by_value)))
    return tab->disabled;

  return FALSE;
}
