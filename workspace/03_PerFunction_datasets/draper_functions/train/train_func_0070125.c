channels_4char STDVAR
{
  Function F = (Function) cd;

  BADARGS(5, 5, " nick uhost hand chan/param");

  CHECKVALIDITY(channels_4char);
  F(argv[1], argv[2], argv[3], argv[4]);
  return TCL_OK;
}
