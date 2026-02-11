XS__listhook(pTHX_ CV *perlcv)
{

  int i;
  FETCHWORLDVARS;
  dXSARGS;

  FETCHWORLD;

  if (items < 2) {
    warn(_("%s: Too few arguments"), "listhook");
    XSRETURN_EMPTY;
  }

  if (items == 2) {
    ansitextview_append_string(world->gui, "\n");
    list_hooks(world, SvPV_nolen(ST(1)), NULL);
    XSRETURN_EMPTY;
  }

  i = SvIV(ST(2));
  list_hook(world, SvPV_nolen(ST(1)), i);

  XSRETURN_EMPTY;
}
