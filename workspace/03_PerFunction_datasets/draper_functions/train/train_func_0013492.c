luaK_goiffalse (FuncState *fs, expdesc *e) {
  int pc;
  luaK_dischargevars(fs, e);
  switch (e->k) {
    case VJMP: {
      pc = e->u.info;
      break;
    }
    case VNIL: case VFALSE: {
      pc = NO_JUMP;
      break;
    }
    default: {
      pc = jumponcond(fs, e, 1);
      break;
    }
  }
  luaK_concat(fs, &e->t, pc);
  luaK_patchtohere(fs, e->f);
  e->f = NO_JUMP;
}
