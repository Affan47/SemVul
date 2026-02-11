atk_component_get_extents    (AtkComponent    *component,
                              gint            *x,
                              gint            *y,
                              gint            *width,
                              gint            *height,
                              AtkCoordType    coord_type)
{
  AtkComponentIface *iface = NULL;
  gint local_x, local_y, local_width, local_height;
  gint *real_x, *real_y, *real_width, *real_height;

  g_return_if_fail (ATK_IS_COMPONENT (component));

  if (x)
    real_x = x;
  else
    real_x = &local_x;
  if (y)
    real_y = y;
  else
    real_y = &local_y;
  if (width)
    real_width = width;
  else
    real_width = &local_width;
  if (height)
    real_height = height;
  else
    real_height = &local_height;

  iface = ATK_COMPONENT_GET_IFACE (component);

  if (iface->get_extents)
    (iface->get_extents) (component, real_x, real_y, real_width, real_height, coord_type);
}
