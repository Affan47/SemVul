atspi_accessible_get_image_iface (AtspiAccessible *accessible)
{
  return (_atspi_accessible_is_a (accessible, atspi_interface_image) ?
          g_object_ref (ATSPI_IMAGE (accessible)) : NULL);
}
