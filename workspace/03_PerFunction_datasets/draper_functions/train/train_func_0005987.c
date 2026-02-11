rt_get_data (int bytes, void *data)
{
  int total = 0;

  while (bytes)
    {
      int bytesnow = bytes;

      if (bytesnow > 0xffc0)
	bytesnow = 0xffc0;
      if (rt_queue_command
	  (RTCMD_READBYTES, 0, bytesnow, 0, 0, bytesnow, data) < 0
	  || rt_execute_commands () < 0)
	return -1;
      total += bytesnow;
      bytes -= bytesnow;
      data = (char *) data + bytesnow;
    }
  return 0;
}
