correctcalls (CompileState *compst, int *positions,
                          int from, int to) {
  int i;
  Instruction *code = compst->p->code;
  for (i = from; i < to; i += sizei(&code[i])) {
    if (code[i].i.code == IOpenCall) {
      int n = code[i].i.key;
      int rule = positions[n];
      assert(rule == from || code[rule - 1].i.code == IRet);
      if (code[finaltarget(code, i + 2)].i.code == IRet)
        code[i].i.code = IJmp;
      else
        code[i].i.code = ICall;
      jumptothere(compst, i, rule);
    }
  }
  assert(i == to);
}
