builtin_charidx STDVAR
{
  Function F = (Function) cd;
  int idx;

  BADARGS(3, 3, " handle idx");

  CHECKVALIDITY(builtin_charidx);
  idx = findanyidx(atoi(argv[2]));
  if (idx < 0) {
    Tcl_AppendResult(irp, "invalid idx", NULL);
    return TCL_ERROR;
  }
  Tcl_AppendResult(irp, int_to_base10(F(argv[1], idx)), NULL);

  return TCL_OK;
}
