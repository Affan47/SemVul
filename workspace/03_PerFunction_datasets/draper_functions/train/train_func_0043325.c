atk_component_grab_focus (AtkComponent    *component)
{
  AtkComponentIface *iface = NULL;
  g_return_val_if_fail (ATK_IS_COMPONENT (component), FALSE);

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->grab_focus)
    return (iface->grab_focus) (component);
  else
    return FALSE;
}
