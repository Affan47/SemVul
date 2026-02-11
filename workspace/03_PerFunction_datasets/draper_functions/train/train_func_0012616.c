parse_params(LexState *ls, int needself)
{
  FuncState *fs = ls->fs;
  BCReg nparams = 0;
  lex_check(ls, '(');
  if (needself)
    var_new_lit(ls, nparams++, "self");
  if (ls->token != ')') {
    do {
      if (ls->token == TK_name || (!LJ_52 && ls->token == TK_goto)) {
	var_new(ls, nparams++, lex_str(ls));
      } else if (ls->token == TK_dots) {
	lj_lex_next(ls);
	fs->flags |= PROTO_VARARG;
	break;
      } else {
	err_syntax(ls, LJ_ERR_XPARAM);
      }
    } while (lex_opt(ls, ','));
  }
  var_add(ls, nparams);
  lua_assert(fs->nactvar == nparams);
  bcreg_reserve(fs, nparams);
  lex_check(ls, ')');
  return nparams;
}
