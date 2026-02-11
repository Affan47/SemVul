slot_proxy_switch_location_timer (gpointer user_data)
{
  NautilusDragSlotProxyInfo *drag_info = user_data;

  drag_info->switch_location_timer = 0;

  if (drag_info->is_notebook)
    switch_tab (drag_info);
  else
    switch_location (drag_info);

  return FALSE;
}
