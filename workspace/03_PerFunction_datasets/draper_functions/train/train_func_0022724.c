AST_cmp_return_inst (Node *node, SymTable *st, Program *p, CompContext *cc, bool follow) {
  AST_callCompFunc (node->child, st, p, cc, true);

  p->code[cc->pc++] = _POPL;
  p->code[cc->pc++] = -(cc->arg_c+3);
  p->code[cc->pc++] = _OUT;
  p->code[cc->pc++] = _RETURN;

  if (follow) AST_callCompFunc (node->next, st, p, cc, true);
}
