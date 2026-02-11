gl646_read_reg (usb_dev_handle * handle, unsigned char reg,
		unsigned char *val)
{
  int result;

  result =
    usb_control_msg (handle, 0x00, 0x00, 0x83, 0x00, (char *) &reg, 0x01,
		     TIMEOUT);
  if (result < 0)
    return 0;

  result =
    usb_control_msg (handle, 0x80, 0x00, 0x84, 0x00, (char *) val, 0x01,
		     TIMEOUT);
  if (result < 0)
    return 0;

  return 1;
}
