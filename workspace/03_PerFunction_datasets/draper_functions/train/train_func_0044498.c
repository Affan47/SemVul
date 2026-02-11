st_widget_get_accessible_role (StWidget *widget)
{
  AtkObject *accessible = NULL;
  AtkRole role = ATK_ROLE_INVALID;

  g_return_val_if_fail (ST_IS_WIDGET (widget), ATK_ROLE_INVALID);

  if (widget->priv->accessible_role != ATK_ROLE_INVALID)
    role = widget->priv->accessible_role;
  else if (widget->priv->accessible != NULL)
    role = atk_object_get_role (accessible);

  return role;
}
