DoIsSmiAndBranch(LIsSmiAndBranch* instr) {
  int true_block = chunk_->LookupDestination(instr->true_block_id());
  int false_block = chunk_->LookupDestination(instr->false_block_id());

  Condition is_smi;
  if (instr->InputAt(0)->IsRegister()) {
    Register input = ToRegister(instr->InputAt(0));
    is_smi = masm()->CheckSmi(input);
  } else {
    Operand input = ToOperand(instr->InputAt(0));
    is_smi = masm()->CheckSmi(input);
  }
  EmitBranch(true_block, false_block, is_smi);
}
