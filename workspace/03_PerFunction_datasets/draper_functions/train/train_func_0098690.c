VisitContinueStatement(ContinueStatement* stmt) {
  Comment cmnt(masm_,  "[ ContinueStatement");
  SetStatementPosition(stmt);
  NestedStatement* current = nesting_stack_;
  int stack_depth = 0;
  while (!current->IsContinueTarget(stmt->target())) {
    stack_depth = current->Exit(stack_depth);
    current = current->outer();
  }
  __ Drop(stack_depth);

  Iteration* loop = current->AsIteration();
  __ jmp(loop->continue_target());
}
