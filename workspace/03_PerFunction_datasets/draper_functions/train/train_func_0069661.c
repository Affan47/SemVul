VisitDoWhileStatement(DoWhileStatement* stmt) {
  ASSERT(!HasStackOverflow());
  ASSERT(current_block() != NULL);
  ASSERT(current_block()->HasPredecessor());
  ASSERT(current_block() != NULL);
  PreProcessOsrEntry(stmt);
  HBasicBlock* loop_entry = CreateLoopHeaderBlock();
  current_block()->Goto(loop_entry);
  set_current_block(loop_entry);

  BreakAndContinueInfo break_info(stmt);
  CHECK_BAILOUT(VisitLoopBody(stmt, loop_entry, &break_info));
  HBasicBlock* body_exit =
      JoinContinue(stmt, current_block(), break_info.continue_block());
  HBasicBlock* loop_successor = NULL;
  if (body_exit != NULL && !stmt->cond()->ToBooleanIsTrue()) {
    set_current_block(body_exit);


    body_exit = graph()->CreateBasicBlock();
    loop_successor = graph()->CreateBasicBlock();
    CHECK_BAILOUT(VisitForControl(stmt->cond(), body_exit, loop_successor));
    if (body_exit->HasPredecessor()) {
      body_exit->SetJoinId(stmt->BackEdgeId());
    } else {
      body_exit = NULL;
    }
    if (loop_successor->HasPredecessor()) {
      loop_successor->SetJoinId(stmt->ExitId());
    } else {
      loop_successor = NULL;
    }
  }
  HBasicBlock* loop_exit = CreateLoop(stmt,
                                      loop_entry,
                                      body_exit,
                                      loop_successor,
                                      break_info.break_block());
  set_current_block(loop_exit);
}
