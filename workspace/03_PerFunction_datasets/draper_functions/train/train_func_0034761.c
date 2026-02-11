handle_status (unsigned char *argbuf, size_t arglen)
{
  long err;
  struct pcsc_readerstate_s rdrstates[1];
  int status;
  unsigned char buf[20];

  (void)argbuf;
  (void)arglen;

  if (!driver_is_open)
    {
      fprintf (stderr, PGM ": PC/SC has not yet been opened\n");
      request_failed (-1);
      return;
    }

  memset (rdrstates, 0, sizeof *rdrstates);
  rdrstates[0].reader = current_rdrname;
  rdrstates[0].current_state = PCSC_STATE_UNAWARE;
  err = pcsc_get_status_change (pcsc_context,
                                0,
                                rdrstates, 1);
  if (err == 0x8010000a)
    err = 0;
  if (err)
    {
      fprintf (stderr, PGM": pcsc_get_status_change failed: %s (0x%lx)\n",
               pcsc_error_string (err), err);
      request_failed (err);
      return;
    }

  status = 0;
  if ( !(rdrstates[0].event_state & PCSC_STATE_UNKNOWN) )
    {
      if ( (rdrstates[0].event_state & PCSC_STATE_PRESENT) )
	{
	  status |= 2;
	  if ( !(rdrstates[0].event_state & PCSC_STATE_MUTE) )
	    status |= 4;
	}


      if ( (status & 6) == 6
           && !(rdrstates[0].event_state & PCSC_STATE_INUSE) )
        status |= 1;
    }


  buf[0] = 0;
  buf[1] = 0;
  buf[2] = 0;
  buf[3] = status;

  buf[4] = (rdrstates[0].event_state >> 24);
  buf[5] = (rdrstates[0].event_state >> 16);
  buf[6] = (rdrstates[0].event_state >>  8);
  buf[7] = (rdrstates[0].event_state >>  0);

  buf[8]  = (pcsc_protocol >> 24);
  buf[9]  = (pcsc_protocol >> 16);
  buf[10] = (pcsc_protocol >> 8);
  buf[11] = (pcsc_protocol);

  request_succeeded (buf, 8);
}
