ReturnInstruction(HInstruction* instr, int ast_id) {
  owner()->AddInstruction(instr);
  if (instr->HasSideEffects()) owner()->AddSimulate(ast_id);
}
