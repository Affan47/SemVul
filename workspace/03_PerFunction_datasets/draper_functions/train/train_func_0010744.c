tcl_loadmodule STDVAR
{
  const char *p;

  BADARGS(2, 2, " module-name");

  p = module_load(argv[1]);
  if (p && strcmp(p, MOD_ALREADYLOAD) && !strcmp(argv[0], "loadmodule"))
    putlog(LOG_MISC, "*", "%s %s: %s", MOD_CANTLOADMOD, argv[1], p);
  Tcl_AppendResult(irp, p, NULL);
  return TCL_OK;
}
