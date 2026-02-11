pie_set_window (Pie_Scanner * scanner)
{
  unsigned char buffer[128];
  size_t size;
  SANE_Status status;
  unsigned char *data;
  double x, dpmm;

  DBG (DBG_proc, "pie_set_window\n");

  size = 14;

  set_write_length (swrite.cmd, size);

  memcpy (buffer, swrite.cmd, swrite.size);

  data = buffer + swrite.size;
  memset (data, 0, size);

  set_command (data, SET_SCAN_FRAME);
  set_data_length (data, size - 4);

  data[4] = 0x80;
  if (scanner->colormode == HALFTONE)
    data[4] |= 0x40;

  dpmm = (double) scanner->device->inquiry_pixel_resolution / MM_PER_INCH;

  x = SANE_UNFIX (scanner->val[OPT_TL_X].w) * dpmm;
  set_data (data, 6, (int) x, 2);
  DBG (DBG_info, "TL_X: %d\n", (int) x);

  x = SANE_UNFIX (scanner->val[OPT_TL_Y].w) * dpmm;
  set_data (data, 8, (int) x, 2);
  DBG (DBG_info, "TL_Y: %d\n", (int) x);

  x = SANE_UNFIX (scanner->val[OPT_BR_X].w) * dpmm;
  set_data (data, 10, (int) x, 2);
  DBG (DBG_info, "BR_X: %d\n", (int) x);

  x = SANE_UNFIX (scanner->val[OPT_BR_Y].w) * dpmm;
  set_data (data, 12, (int) x, 2);
  DBG (DBG_info, "BR_Y: %d\n", (int) x);

  status =
    sanei_scsi_cmd (scanner->sfd, buffer, swrite.size + size, NULL, NULL);
  if (status)
    {
      DBG (DBG_error, "pie_set_window: write command returned status %s\n",
	   sane_strstatus (status));
    }

  return status;
}
