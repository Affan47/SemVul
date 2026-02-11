rt_get_available_bytes (void)
{
  unsigned char data[3];

  if (rt_queue_command (RTCMD_BYTESAVAIL, 0, 3, 0, 0, 3, data) < 0 ||
      rt_execute_commands () < 0)
    return -1;
  return ((unsigned) data[0]) |
    ((unsigned) data[1] << 8) | ((unsigned) data[2] << 16);
}
