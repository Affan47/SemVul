read_data (AgfaFocus_Scanner * s, SANE_Byte *buf, int lines, int bpl)
{
  struct {
   Byte cmd;
   Byte lun;
   Byte re1[4];
   Byte tr_len[3];
   Byte ctrl;
  } cmd;

  SANE_Status status;
  size_t size;
  unsigned int i;

  memset (&cmd, 0, sizeof (cmd));

  cmd.cmd = 0x28;

  set_size (cmd.tr_len, 3, lines);
  size = lines * bpl;

  status = sanei_scsi_cmd (s->fd, &cmd, sizeof (cmd), buf, &size);

  if (status != SANE_STATUS_GOOD)
    {
      DBG (1, "sanei_scsi_cmd() = %d\n", status);
      return SANE_STATUS_IO_ERROR;
    }

  if (size != ((unsigned int) lines * bpl))
    {
      DBG (1, "sanei_scsi_cmd(): got %lu bytes, expected %d\n",
	   (u_long) size, lines * bpl);
      return SANE_STATUS_INVAL;
    }

  DBG (1, "Got %lu bytes\n", (u_long) size);


  if (s->bpp != 1)
    {
      if (s->bpp != 6)
	for (i = 0; i < size; i++)
	  buf[i] = 255 - buf[i];
      else
	for (i = 0; i < size; i++)
	  buf[i] = 255 - ((buf[i] * 256.0f) / 64.0f);
    }

  s->lines_available -= lines;

  return SANE_STATUS_GOOD;
}
