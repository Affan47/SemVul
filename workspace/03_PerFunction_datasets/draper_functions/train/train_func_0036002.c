handle_interrupt (pixma_t * s, int timeout)
{
  uint8_t buf[16];
  int len;

  len = pixma_wait_interrupt (s->io, buf, sizeof (buf), timeout);
  if (len == PIXMA_ETIMEDOUT)
    return 0;
  if (len < 0)
    return len;
  switch (s->cfg->pid)
    {
    case MP360_PID:
    case MP370_PID:
    case MP375R_PID:
    case MP390_PID:
    case MF5730_PID:
    case MF5750_PID:
    case MF5770_PID:
    case MF3110_PID:
    case IR1020_PID:
      if (len != 16)
	{
	  PDBG (pixma_dbg
		(1, "WARNING:unexpected interrupt packet length %d\n", len));
	  return PIXMA_EPROTO;
	}
      if (buf[12] & 0x40)
	query_status (s);
      if (buf[10] & 0x40)
	send_time (s);

      if (buf[15] & 1)
	s->events = PIXMA_EV_BUTTON2;
      if (buf[15] & 2)
	s->events = PIXMA_EV_BUTTON1;
      break;

    case MP700_PID:
    case MP730_PID:
    case MP710_PID:
    case MP740_PID:
      if (len != 8)
	{
	  PDBG (pixma_dbg
		(1, "WARNING:unexpected interrupt packet length %d\n", len));
	  return PIXMA_EPROTO;
	}
      if (buf[7] & 0x10)
	s->events = PIXMA_EV_BUTTON1;
      if (buf[5] & 8)
	send_time (s);
      break;

    default:
      PDBG (pixma_dbg (1, "WARNING:unknown interrupt, please report!\n"));
      PDBG (pixma_hexdump (1, buf, len));
    }
  return 1;
}
