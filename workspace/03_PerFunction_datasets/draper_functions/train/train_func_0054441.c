ReturnInstruction(HInstruction* instr, int ast_id) {
  ASSERT(!instr->IsControlInstruction());
  HGraphBuilder* builder = owner();
  builder->AddInstruction(instr);


  if (instr->HasSideEffects()) {
    builder->Push(instr);
    builder->AddSimulate(ast_id);
    builder->Pop();
  }
  BuildBranch(instr);
}
