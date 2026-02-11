parse_chunk(LexState *ls)
{
  int islast = 0;
  synlevel_begin(ls);
  while (!islast && !endofblock(ls->token)) {
    islast = parse_stmt(ls);
    lex_opt(ls, ';');
    lua_assert(ls->fs->framesize >= ls->fs->freereg &&
	       ls->fs->freereg >= ls->fs->nactvar);
    ls->fs->freereg = ls->fs->nactvar;
  }
  synlevel_end(ls);
}
