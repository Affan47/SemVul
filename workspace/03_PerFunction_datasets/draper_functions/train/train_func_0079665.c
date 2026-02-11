forbody (LexState *ls, int base, int line, int nvars, int isnum) {

  BlockCnt bl;
  FuncState *fs = ls->fs;
  int prep, endfor;
  adjustlocalvars(ls, 3);
  checknext(ls, TK_DO);
  prep = isnum ? luaK_codeAsBx(fs, OP_FORPREP, base, NO_JUMP) : luaK_jump(fs);
  enterblock(fs, &bl, 0);
  adjustlocalvars(ls, nvars);
  luaK_reserveregs(fs, nvars);
  block(ls);
  leaveblock(fs);
  luaK_patchtohere(fs, prep);
  if (isnum)
    endfor = luaK_codeAsBx(fs, OP_FORLOOP, base, NO_JUMP);
  else {
    luaK_codeABC(fs, OP_TFORCALL, base, 0, nvars);
    luaK_fixline(fs, line);
    endfor = luaK_codeAsBx(fs, OP_TFORLOOP, base + 2, NO_JUMP);
  }
  luaK_patchlist(fs, endfor, prep + 1);
  luaK_fixline(fs, line);
}
