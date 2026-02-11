ata_get_smart_values(int device, unsigned char* buff) {
  unsigned char  cmd[516] = { WIN_SMART, 0, SMART_READ_VALUES, 1 };
  int            ret;

  ret = ioctl(device, HDIO_DRIVE_CMD, cmd);
  if(ret)
    return ret;
  memcpy(buff, cmd+4, 512);
  return 0;
}
