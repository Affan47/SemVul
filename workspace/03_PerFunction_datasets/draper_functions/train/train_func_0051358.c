cam_device_open (CamDevice * device, const char *filename)
{
  ca_caps_t ca_caps;
  int ret;
  int i;

  g_return_val_if_fail (device != NULL, FALSE);
  g_return_val_if_fail (device->state == CAM_DEVICE_STATE_CLOSED, FALSE);
  g_return_val_if_fail (filename != NULL, FALSE);

  GST_INFO ("opening ca device %s", filename);

  ret = open (filename, O_RDWR);
  if (ret == -1) {
    GST_ERROR ("can't open ca device: %s", strerror (errno));
    return FALSE;
  }

  device->fd = ret;

  ret = ioctl (device->fd, CA_RESET);
  sleep (1);


  ret = ioctl (device->fd, CA_GET_CAP, &ca_caps);
  if (ret == -1) {
    GST_ERROR ("CA_GET_CAP ioctl failed: %s", strerror (errno));
    reset_state (device);
    return FALSE;
  }

  device->tl = cam_tl_new (device->fd);
  device->sl = cam_sl_new (device->tl);
  device->al = cam_al_new (device->sl);

  device->mgr = cam_resource_manager_new ();
  cam_al_install (device->al, CAM_AL_APPLICATION (device->mgr));

  device->info = cam_application_info_new ();
  cam_al_install (device->al, CAM_AL_APPLICATION (device->info));

  device->cas = cam_conditional_access_new ();
  cam_al_install (device->al, CAM_AL_APPLICATION (device->cas));


  for (i = 0; i < ca_caps.slot_num; ++i) {
    CamTLConnection *connection;

    ret = cam_tl_create_connection (device->tl, i, &connection);
    if (CAM_FAILED (ret)) {


      GST_WARNING ("connection to slot %d failed, error: %d", i, ret);
      continue;
    }
  }

  if (g_hash_table_size (device->tl->connections) == 0) {
    GST_ERROR ("couldn't connect to any slot");

    reset_state (device);
    return FALSE;
  }

  device->state = CAM_DEVICE_STATE_OPEN;
  device->filename = g_strdup (filename);


  cam_tl_read_all (device->tl, TRUE);

  return TRUE;
}
