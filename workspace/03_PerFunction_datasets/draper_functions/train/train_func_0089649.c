statlist (LexState *ls) {

  while (!block_follow(ls, 1)) {
    if (ls->t.token == TK_RETURN) {
      statement(ls);
      return;
    }
    statement(ls);
  }
}
