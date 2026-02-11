read_serial_number (scanner_info_t * si)
{
  uint8_t unicode[2 * (PIXMA_MAX_ID_LEN - 9) + 2];
  uint8_t ddesc[18];
  int i, len, iSerialNumber;
  SANE_Int usb;
  SANE_Status status;
  char *serial = si->serial;

  u16tohex (si->cfg->vid, serial);
  u16tohex (si->cfg->pid, serial + 4);

  if (SANE_STATUS_GOOD != sanei_usb_open (si->devname, &usb))
    return;
  if (get_descriptor (usb, USB_DT_DEVICE, 0, 0, 18, ddesc)
      != SANE_STATUS_GOOD)
    goto done;
  iSerialNumber = ddesc[16];
  if (iSerialNumber != 0)
    {


      if (get_string_descriptor (usb, 0, 0, 4, unicode) != SANE_STATUS_GOOD)
        goto done;

      status = get_string_descriptor (usb, iSerialNumber,
                                      unicode[3] * 256 + unicode[2],
                                      sizeof (unicode), unicode);
      if (status != SANE_STATUS_GOOD)
        goto done;

      len = unicode[0];
      if (len > (int) sizeof (unicode))
        {
          len = sizeof (unicode);
          PDBG (pixma_dbg (1, "WARNING:Truncated serial number\n"));
        }
            serial[8] = '_';
            for (i = 2; i < len; i += 2)
        {
          serial[9 + i / 2 - 1] = unicode[i];
        }
      serial[9 + i / 2 - 1] = '\0';
    }
  else
    {
      PDBG (pixma_dbg (1, "WARNING:No serial number\n"));
    }
done:
  sanei_usb_close (usb);
}
