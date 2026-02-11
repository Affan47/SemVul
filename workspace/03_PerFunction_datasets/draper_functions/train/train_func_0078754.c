lash_client_proxy_save(const char * dest, const char * app_dir)
{
  if (!cdbus_call(0, dest, "/", IFACE_LASH_CLIENT, "Save", "s", &app_dir, ""))
  {
    log_error(IFACE_LASH_CLIENT "::Save() failed.");
    return false;
  }

  return true;
}
