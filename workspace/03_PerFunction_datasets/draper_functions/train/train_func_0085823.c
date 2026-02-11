dd_get_linestr(pTHX) {
  if (!DD_HAVE_PARSER) {
    return NULL;
  }
  return SvPVX(PL_linestr);
}
