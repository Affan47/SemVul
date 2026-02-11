str_checkname (LexState *ls) {
  TString *ts;
  check_condition(ls, (ls->t.token == TK_NAME), "<name> expected");
  ts = ls->t.seminfo.ts;
  next(ls);
  return ts;
}
