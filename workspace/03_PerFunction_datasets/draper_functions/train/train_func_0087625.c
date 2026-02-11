tcl_reloadhelp STDVAR
{
  BADARGS(1, 1, "");

  reload_help_data();
  return TCL_OK;
}
