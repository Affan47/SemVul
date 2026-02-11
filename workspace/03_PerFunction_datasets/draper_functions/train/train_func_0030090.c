builtin_3char STDVAR
{
  Function F = (Function) cd;

  BADARGS(4, 4, " from to args");

  CHECKVALIDITY(builtin_3char);
  F(argv[1], argv[2], argv[3]);
  return TCL_OK;
}
