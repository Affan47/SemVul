prefixexp (LexState *ls, vardesc *v, stack_op *s) {

  while (ls->token == NOT || ls->token == '-') {
    push(ls, s, (ls->token==NOT)?INDNOT:INDMINUS);
    next(ls);
  }
  simpleexp(ls, v, s);
}
