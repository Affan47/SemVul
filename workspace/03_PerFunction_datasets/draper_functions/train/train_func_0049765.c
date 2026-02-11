cam_sw_client_open (CamSwClient * client, const char *sock_path)
{
  struct sockaddr_un addr;
  int ret;

  g_return_val_if_fail (client != NULL, FALSE);
  g_return_val_if_fail (client->state == CAM_SW_CLIENT_STATE_CLOSED, FALSE);
  g_return_val_if_fail (sock_path != NULL, FALSE);

  addr.sun_family = AF_UNIX;
  strncpy (addr.sun_path, sock_path, sizeof (addr.sun_path));

  GST_INFO ("connecting to softcam socket: %s", sock_path);
  client->sock = socket (PF_UNIX, SOCK_STREAM, 0);
  ret =
      connect (client->sock, (struct sockaddr *) &addr,
      sizeof (struct sockaddr_un));
  if (ret != 0) {
    GST_ERROR ("error opening softcam socket %s, error: %s",
        sock_path, strerror (errno));

    return FALSE;
  }

  client->sock_path = g_strdup (sock_path);
  client->state = CAM_SW_CLIENT_STATE_OPEN;

  return TRUE;
}
