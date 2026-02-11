parse_repeat(LexState *ls, BCLine line)
{
  FuncState *fs = ls->fs;
  BCPos loop = fs->lasttarget = fs->pc;
  BCPos condexit;
  FuncScope bl1, bl2;
  fscope_begin(fs, &bl1, FSCOPE_LOOP);
  fscope_begin(fs, &bl2, 0);
  lj_lex_next(ls);
  bcemit_AD(fs, BC_LOOP, fs->nactvar, 0);
  parse_chunk(ls);
  lex_match(ls, TK_until, TK_repeat, line);
  condexit = expr_cond(ls);
  if (!(bl2.flags & FSCOPE_UPVAL)) {
    fscope_end(fs);
  } else {
    parse_break(ls);
    jmp_tohere(fs, condexit);
    fscope_end(fs);
    condexit = bcemit_jmp(fs);
  }
  jmp_patch(fs, condexit, loop);
  jmp_patchins(fs, loop, fs->pc);
  fscope_end(fs);
}
