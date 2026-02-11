request_push_button_status (SANE_Handle handle, SANE_Bool * theButtonStatus)
{
  Epson_Scanner *s = (Epson_Scanner *) handle;
  SANE_Status status;
  int len;
  u_char param[3];
  u_char result[4];
  u_char *buf;

  DBG (5, "request_push_button_status()\n");

  if (s->hw->cmd->request_push_button_status == 0)
  {
    DBG (1, "push button status unsupported\n");
    return SANE_STATUS_UNSUPPORTED;
  }

  param[0] = ESC;
  param[1] = s->hw->cmd->request_push_button_status;
  param[2] = '\0';

  send (s, param, 2, &status);

  if (SANE_STATUS_GOOD != status)
  {
    DBG (1, "error sending command\n");
    return status;
  }

  len = 4;

  receive (s, result, len, &status);
  if (SANE_STATUS_GOOD != status)
    return status;

  len = result[3] << 8 | result[2];
  buf = alloca (len);

  receive (s, buf, len, &status);

  DBG (1, "Push button status = %d\n", buf[0] & 0x01);
  *theButtonStatus = ((buf[0] & 0x01) != 0);

  return (SANE_STATUS_GOOD);
}
