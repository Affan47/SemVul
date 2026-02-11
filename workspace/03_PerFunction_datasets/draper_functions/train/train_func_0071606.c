tcl_dnslookup STDVAR
{
  struct in_addr inaddr;
  Tcl_DString paras;

  if (argc < 3) {
    Tcl_AppendResult(irp, "wrong # args: should be \"", argv[0],
                     " ip-address/hostname proc ?args...?\"", NULL);
    return TCL_ERROR;
  }

  Tcl_DStringInit(&paras);
  if (argc > 3) {
    int p;

    for (p = 3; p < argc; p++)
      Tcl_DStringAppendElement(&paras, argv[p]);
  }

  if (egg_inet_aton(argv[1], &inaddr))
    tcl_dnshostbyip(ntohl(inaddr.s_addr), argv[2], Tcl_DStringValue(&paras));
  else
    tcl_dnsipbyhost(argv[1], argv[2], Tcl_DStringValue(&paras));

  Tcl_DStringFree(&paras);
  return TCL_OK;
}
