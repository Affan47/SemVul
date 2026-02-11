string_constant (FuncState *fs, TString *s) {
  Proto *f = fs->f;
  int c = s->u.s.constindex;
  if (c >= f->nkstr || f->kstr[c] != s) {
    luaM_growvector(fs->L, f->kstr, f->nkstr, 1, TString *,
                    "constant table overflow", MAXARG_U);
    c = f->nkstr++;
    f->kstr[c] = s;
    s->u.s.constindex = c;
  }
  return c;
}
