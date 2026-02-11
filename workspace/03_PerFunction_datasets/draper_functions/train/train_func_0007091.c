st_widget_accessible_get_role (AtkObject *obj)
{
  StWidget *widget = NULL;

  g_return_val_if_fail (ST_IS_WIDGET_ACCESSIBLE (obj), ATK_ROLE_INVALID);

  widget = ST_WIDGET (atk_gobject_accessible_get_object (ATK_GOBJECT_ACCESSIBLE (obj)));

  if (widget == NULL)
    return ATK_ROLE_INVALID;

  if (widget->priv->accessible_role != ATK_ROLE_INVALID)
    return widget->priv->accessible_role;

  return ATK_OBJECT_CLASS (st_widget_accessible_parent_class)->get_role (obj);
}
