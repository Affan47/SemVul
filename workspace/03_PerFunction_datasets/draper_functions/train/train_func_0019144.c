leo_set_window (Leo_Scanner * dev)
{
  size_t size;
  CDB cdb;
  unsigned char window[48];
  SANE_Status status;

  DBG (DBG_proc, "leo_set_window: enter\n");

  size = sizeof (window);
  MKSCSI_SET_WINDOW (cdb, size);

  memset (window, 0, size);


  window[7] = sizeof (window) - 8;
  window[1] = sizeof (window) - 2;


  Ito16 (dev->x_resolution, &window[10]);
  Ito16 (dev->y_resolution, &window[12]);


  Ito32 (dev->x_tl, &window[14]);
  Ito32 (dev->y_tl, &window[18]);


  Ito32 (dev->width, &window[22]);
  Ito32 (dev->length, &window[26]);


  switch (dev->scan_mode)
    {
    case LEO_BW:
      window[33] = 0x00;
      break;
    case LEO_HALFTONE:
      window[33] = 0x01;
      break;
    case LEO_GRAYSCALE:
      window[33] = 0x02;
      break;
    case LEO_COLOR:
      window[33] = 0x05;
      break;
    }


  window[34] = dev->depth;


  window[31] = 0x80;
  window[43] = 0x01;

  hexdump (DBG_info2, "windows", window, sizeof (window));

  status = sanei_scsi_cmd2 (dev->sfd, cdb.data, cdb.len,
			    window, sizeof (window), NULL, NULL);

  DBG (DBG_proc, "leo_set_window: exit, status=%d\n", status);

  return status;
}
