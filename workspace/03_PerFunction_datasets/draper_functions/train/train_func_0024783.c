pushback_place_name(struct zipcode_line *zl, char *pn)
{
  if (pn[0] == '#') {
    return ;
  }
  zl->strs = realloc(zl->strs, sizeof(xstr *) * (zl->nr + 1));
  zl->strs[zl->nr] = anthy_cstr_to_xstr(pn, ANTHY_EUC_JP_ENCODING);
  zl->nr++;
}
