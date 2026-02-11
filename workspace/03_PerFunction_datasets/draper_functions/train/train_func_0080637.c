Goto(HBasicBlock* block, bool include_stack_check) {
  AddSimulate(AstNode::kNoNumber);
  HGoto* instr = new HGoto(block);
  instr->set_include_stack_check(include_stack_check);
  Finish(instr);
}
