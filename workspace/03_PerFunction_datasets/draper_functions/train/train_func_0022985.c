cond (LexState *ls, expdesc *v) {

  expr(ls, v);
  if (v->k == VNIL) v->k = VFALSE;
  luaK_goiftrue(ls->fs, v);
  luaK_patchtohere(ls->fs, v->t);
}
