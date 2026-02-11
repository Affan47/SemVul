pio_wait (const Port port, u_char val, u_char mask)
{
  int stat = 0;
  long poll_count = 0;
  time_t start = time(NULL);

  DBG (DL60, "wait on port 0x%03lx for %02x mask %02x\n",
       port->base, (int) val, (int) mask);
  DBG (DL61, "   BUSY    %s\n", (mask & PIO_STAT_BUSY) ?
       (val & PIO_STAT_BUSY ? "on" : "off") : "-");
  DBG (DL61, "   NACKNLG %s\n",
       (mask & PIO_STAT_NACKNLG) ? (val & PIO_STAT_NACKNLG ? "on" : "off")
       : "-");
  for (;;)
    {
      ++poll_count;
      stat = inb (port->base + PIO_STAT);
      if ((stat & mask) == (val & mask))
	{
	  DBG (DL60, "got %02x after %ld tries\n", stat, poll_count);
	  DBG (DL61, "   BUSY    %s\n", stat & PIO_STAT_BUSY ? "on" : "off");
	  DBG (DL61, "   NACKNLG %s\n",
	       stat & PIO_STAT_NACKNLG ? "on" : "off");

	  return stat;
	}
      if(poll_count>1000)
        {
          if ((port->max_time_seconds>0) && (time(NULL)-start >= port->max_time_seconds))
	    break;
          usleep(1);
        }

    }
  DBG (DL60, "got %02x aborting after %ld\n", stat, poll_count);
  DBG (DL61, "   BUSY    %s\n", stat & PIO_STAT_BUSY ? "on" : "off");
  DBG (DL61, "   NACKNLG %s\n", stat & PIO_STAT_NACKNLG ? "on" : "off");
  DBG (1, "polling time out, abort\n");
  exit (-1);
}
