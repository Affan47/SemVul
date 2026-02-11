do_device_index (const char *device)
{
  size_t i;
  int ret = -1;
  CLEANUP_FREE_STRING_LIST char **devices = do_list_devices ();

  if (devices == NULL)
    return -1;

  for (i = 0; devices[i] != NULL; ++i) {
    if (STREQ (device, devices[i]))
      ret = (int) i;
  }

  if (ret == -1)
    reply_with_error ("device not found");

  return ret;
}
