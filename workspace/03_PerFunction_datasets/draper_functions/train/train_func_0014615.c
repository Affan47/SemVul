DoObjectLiteral(HObjectLiteral* instr) {
  return MarkAsCall(DefineFixed(new LObjectLiteral, rax), instr);
}
