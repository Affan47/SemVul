kvs40xx_read_picture_element (struct scanner * s, unsigned side,
			      SANE_Parameters * p)
{
  SANE_Status status;
  struct cmd c = {
     {0}, 10,
     NULL, 16,
     CMD_IN
  };
  u32 *data;
  c.cmd[0] = READ_10;
  c.cmd[2] = 0x80;
  c.cmd[5] = side;
  set24 (c.cmd + 6, c.data_size);

  status = send_command (s, &c);
  if (status)
    return status;
  data = (u32 *) c.data;
  p->pixels_per_line = be2cpu32 (data[0]);
  p->lines = be2cpu32 (data[1]);

  return SANE_STATUS_GOOD;
}
