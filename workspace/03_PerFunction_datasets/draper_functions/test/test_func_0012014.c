cs2_close (cs2_t * s)
{
  cs2_xfree (s->lut_r);
  cs2_xfree (s->lut_g);
  cs2_xfree (s->lut_b);
  cs2_xfree (s->lut_neutral);
  cs2_xfree (s->infrared_buf);
  cs2_xfree (s->line_buf);

  switch (s->interface)
    {
    case CS2_INTERFACE_UNKNOWN:
      DBG (1, "BUG: cs2_close(): Unknown interface number.\n");
      break;
    case CS2_INTERFACE_SCSI:
      sanei_scsi_close (s->fd);
      open_devices--;
      break;
    case CS2_INTERFACE_USB:
      sanei_usb_close (s->fd);
      open_devices--;
      break;
    }

  cs2_xfree (s);
}
