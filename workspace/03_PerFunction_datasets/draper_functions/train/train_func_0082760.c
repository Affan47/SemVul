stv680_reset_vidcam (Stv680_Vidcam * dev)
{
  SANE_Status status;
  size_t sizew;
  size_t sizer;

  DBG (DBG_proc, "stv680_reset_vidcam: enter\n");

  sizew = dev->windoww_size;
  sizer = dev->windowr_size;

  memset (dev->windoww, 0, sizew);
  memset (dev->windowr, 0, sizer);

  sizew = 0x00;
  status =
    sanei_usb_control_msg (dev->fd, 0x41, 0x0a, 0x0000, 0, sizew,
			   dev->windoww);
  if (status != SANE_STATUS_GOOD)
    {
      return status;
    }
  DBG (DBG_proc, "stv680_reset_vidcam: CMDID_STOP_VIDEO end\n");


  sizew = 0x00;
  status =
    sanei_usb_control_msg (dev->fd, 0x41, 0x04, 0x0000, 0, sizew,
			   dev->windoww);
  if (status != SANE_STATUS_GOOD)
    {
      return status;
    }
  DBG (DBG_proc, "stv680_reset_vidcam: CMDID_CANCEL_TRANSACTION end\n");
  sizer = 0x02;
  DBG (DBG_proc, "stv680_reset_vidcam: CMDID_GET_LAST_ERROR begin\n");
  status =
    sanei_usb_control_msg (dev->fd, 0xc1, 0x80, 0x0000, 0, sizer,
			   dev->windowr);
  if (status != SANE_STATUS_GOOD)
    {

      DBG (DBG_proc,
	   "stv680_reset_vidcam: last error: %i, command = 0x%x\n",
	   dev->windowr[0], dev->windowr[1]);
      return status;
    }
  else
    {
      DBG (DBG_proc, "stv680_reset_vidcam: Camera reset to idle mode.\n");
    }
  hexdump (DBG_info2, "stv680_reset_vidcam: CMDID_GET_LAST_ERROR",
	   dev->windowr, sizer);


  status = SANE_STATUS_GOOD;
  DBG (DBG_proc, "stv680_reset_vidcam: exit\n");

  return status;
}
