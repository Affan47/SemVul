studio_proxy_get_name(char ** name_ptr)
{
  const char * name;
  if (!cdbus_call(0, SERVICE_NAME, STUDIO_OBJECT_PATH, IFACE_STUDIO, "GetName", "", "s", &name))
  {
    return false;
  }

  *name_ptr = strdup(name);
  if (*name_ptr == NULL)
  {
    log_error("strdup() failed to duplicate studio name");
    return false;
  }

  return true;
}
