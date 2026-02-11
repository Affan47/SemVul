pushupvalue (LexState *ls, TaggedString *n) {
  if (ls->fs->prev == NULL)
    luaX_syntaxerror(ls, "cannot access upvalue in main", n->str);
  if (aux_localname(ls->fs, n) >= 0)
    luaX_syntaxerror(ls, "cannot access an upvalue in current scope", n->str);
  code_oparg(ls, PUSHUPVALUE, indexupvalue(ls, n), 1);
}
