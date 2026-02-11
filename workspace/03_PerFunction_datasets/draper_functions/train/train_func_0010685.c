LIBRARY_get_interface_by_name(const char *name, int version, void *iface)
{
  COMPONENT *comp;

  comp = COMPONENT_find(name);
  if (!comp || !comp->library)
    return TRUE;

  LIBRARY_get_interface(comp->library, version, iface);
  return FALSE;
}
