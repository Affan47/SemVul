tcl_putdccraw STDVAR
{
  int i, j = 0, z;

  BADARGS(4, 4, " idx size text");

  z = atoi(argv[1]);
  for (i = 0; i < dcc_total; i++) {
    if (!z && !strcmp(dcc[i].nick, "(server)")) {
      j = dcc[i].sock;
      break;
    } else if (dcc[i].sock == z) {
      j = dcc[i].sock;
      break;
    }
  }
  if (i == dcc_total) {
    Tcl_AppendResult(irp, "invalid idx", NULL);
    return TCL_ERROR;
  }
  tputs(j, argv[3], atoi(argv[2]));
  return TCL_OK;
}
