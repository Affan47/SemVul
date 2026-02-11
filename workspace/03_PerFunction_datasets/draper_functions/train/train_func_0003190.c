teardown(int chan)
  {
  auto char sx[BUFSIZ];


  if (!Q931dmp)
    logger(chan);

  chanused[chan] = 0;

  call[chan].disconnect = call[chan].connect;
  call[chan].cause = 0x66;

  addlist(chan, SETUP, 2);

  sprintf(sx, "HANGUP (Timeout)" );
  info(chan, PRT_SHOWHANGUP, STATE_HANGUP, sx);

  if (sound)
    ringer(chan, RING_HANGUP);

  clearchan(chan, 1);
}
