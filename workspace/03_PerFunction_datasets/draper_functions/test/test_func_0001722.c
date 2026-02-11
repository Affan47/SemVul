tcl_console STDVAR
{
  int i, j, pls, arg;
  module_entry *me;

  BADARGS(2, 4, " idx ?channel? ?console-modes?");

  i = findidx(atoi(argv[1]));
  if (i < 0 || dcc[i].type != &DCC_CHAT) {
    Tcl_AppendResult(irp, "invalid idx", NULL);
    return TCL_ERROR;
  }
  pls = 1;

  for (arg = 2; arg < argc; arg++) {
    if (argv[arg][0] && ((strchr(CHANMETA, argv[arg][0]) != NULL) ||
        (argv[arg][0] == '*'))) {
      if ((argv[arg][0] != '*') && (!findchan_by_dname(argv[arg]))) {


        if (argv[arg][0] == '+')
          goto do_console_flags;
        Tcl_AppendResult(irp, "invalid channel", NULL);
        return TCL_ERROR;
      }
      strncpyz(dcc[i].u.chat->con_chan, argv[arg], 81);
    } else {
      if ((argv[arg][0] != '+') && (argv[arg][0] != '-'))
        dcc[i].u.chat->con_flags = 0;
    do_console_flags:
      for (j = 0; j < strlen(argv[arg]); j++) {
        if (argv[arg][j] == '+')
          pls = 1;
        else if (argv[arg][j] == '-')
          pls = -1;
        else {
          char s[2];

          s[0] = argv[arg][j];
          s[1] = 0;
          if (pls == 1)
            dcc[i].u.chat->con_flags |= logmodes(s);
          else
            dcc[i].u.chat->con_flags &= ~logmodes(s);
        }
      }
    }
  }
  Tcl_AppendElement(irp, dcc[i].u.chat->con_chan);
  Tcl_AppendElement(irp, masktype(dcc[i].u.chat->con_flags));

  if (argc > 2 && (me = module_find("console", 1, 1))) {
    Function *func = me->funcs;

    (func[CONSOLE_DOSTORE]) (i);
  }
  return TCL_OK;
}
