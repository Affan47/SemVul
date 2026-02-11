XS_ispermanent(pTHX_ CV *perlcv)
{
  char    *var;
  GSList  *list;
  FETCHWORLDVARSFULL;
  dXSARGS;

  FETCHWORLDFULL;

  if (items < 2) {
    warn(_("%s: Too few arguments"), "ispermanent");
    XSRETURN_EMPTY;
  }

  var = SvPV_nolen(ST(1));

  list = g_slist_find_custom(world->permanent_variables,
                             var,
                             (GCompareFunc) strcmp);
  if (list) {
    XST_mIV(0, TRUE);
  } else {
    XST_mIV(0, FALSE);
  }

  XSRETURN(1);
}
