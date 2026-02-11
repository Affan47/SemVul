tcl_dccputchan STDVAR
{
  int chan;
  char msg[401];

  BADARGS(3, 3, " channel message");

  chan = atoi(argv[1]);
  if ((chan < 0) || (chan > 199999)) {
    Tcl_AppendResult(irp, "channel out of range; must be 0 through 199999", NULL);
    return TCL_ERROR;
  }
  strncpyz(msg, argv[2], sizeof msg);

  chanout_but(-1, chan, "*** %s\n", argv[2]);
  botnet_send_chan(-1, botnetnick, NULL, chan, argv[2]);
  check_tcl_bcst(botnetnick, chan, argv[2]);
  return TCL_OK;
}
