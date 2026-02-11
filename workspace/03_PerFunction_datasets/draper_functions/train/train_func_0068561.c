smb_to_uri_scheme (GVfsUriMapper *mapper,
                   GMountSpec    *spec)
{
  const gchar *type = g_mount_spec_get (spec, "type");

  if (strcmp ("smb-network", type) == 0 ||
      strcmp ("smb-server", type) == 0 ||
      strcmp ("smb-share", type) == 0)
    return "smb";
  else
    return NULL;
}
