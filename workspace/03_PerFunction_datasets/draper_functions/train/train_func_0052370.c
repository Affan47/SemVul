read_numeral (LexState *ls, SemInfo *seminfo) {
  const char *expo = "Ee";
  int first = ls->current;
  lua_assert(lisdigit(ls->current));
  save_and_next(ls);
  if (first == '0' && check_next(ls, "Xx"))
    expo = "Pp";
  for (;;) {
    if (check_next(ls, expo))
      check_next(ls, "+-");
    if (lisxdigit(ls->current) || ls->current == '.')
      save_and_next(ls);
    else  break;
  }
  save(ls, '\0');
  buffreplace(ls, '.', ls->decpoint);
  if (!buff2d(ls->buff, &seminfo->r))
    trydecpoint(ls, seminfo);
}
