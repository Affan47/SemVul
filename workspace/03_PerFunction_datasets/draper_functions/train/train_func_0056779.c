codegrammar (CompileState *compst, TTree *grammar) {
  int positions[MAXRULES];
  int rulenumber = 0;
  TTree *rule;
  int firstcall = addoffsetinst(compst, ICall);
  int jumptoend = addoffsetinst(compst, IJmp);
  int start = gethere(compst);
  jumptohere(compst, firstcall);
  for (rule = sib1(grammar); rule->tag == TRule; rule = sib2(rule)) {
    positions[rulenumber++] = gethere(compst);
    codegen(compst, sib1(rule), 0, NOINST, fullset);
    addinstruction(compst, IRet, 0);
  }
  assert(rule->tag == TTrue);
  jumptohere(compst, jumptoend);
  correctcalls(compst, positions, start, gethere(compst));
}
