VisitBlock(Block* stmt) {
  ASSERT(!HasStackOverflow());
  ASSERT(current_block() != NULL);
  ASSERT(current_block()->HasPredecessor());
  if (stmt->block_scope() != NULL) {
    return Bailout("ScopedBlock");
  }
  BreakAndContinueInfo break_info(stmt);
  { BreakAndContinueScope push(&break_info, this);
    CHECK_BAILOUT(VisitStatements(stmt->statements()));
  }
  HBasicBlock* break_block = break_info.break_block();
  if (break_block != NULL) {
    if (current_block() != NULL) current_block()->Goto(break_block);
    break_block->SetJoinId(stmt->ExitId());
    set_current_block(break_block);
  }
}
