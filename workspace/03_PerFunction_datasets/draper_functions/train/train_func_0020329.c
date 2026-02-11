XS_dc(pTHX_ CV *perlcv)
{
  FETCHWORLDVARS;
  dXSARGS;

  FETCHWORLD;


  g_idle_add(disconnect_world_idle, world);

  XSRETURN_EMPTY;
}
