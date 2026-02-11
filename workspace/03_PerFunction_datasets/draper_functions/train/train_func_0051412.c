DoCmpTAndBranch(LCmpTAndBranch* instr) {
  Token::Value op = instr->op();
  int true_block = chunk_->LookupDestination(instr->true_block_id());
  int false_block = chunk_->LookupDestination(instr->false_block_id());

  Handle<Code> ic = CompareIC::GetUninitialized(op);
  CallCode(ic, RelocInfo::CODE_TARGET, instr);


  Condition condition = TokenToCondition(op, false);
  if (op == Token::GT || op == Token::LTE) {
    condition = ReverseCondition(condition);
  }
  __ testq(rax, rax);
  EmitBranch(true_block, false_block, condition);
}
