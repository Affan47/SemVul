VisitWithStatement(WithStatement* stmt) {
  Comment cmnt(masm_, "[ WithStatement");
  SetStatementPosition(stmt);

  VisitForStackValue(stmt->expression());
  PushFunctionArgumentForContextAllocation();
  __ CallRuntime(Runtime::kPushWithContext, 2);
  decrement_stack_height();
  StoreToFrameField(StandardFrameConstants::kContextOffset, context_register());

  { WithOrCatch body(this);
    Visit(stmt->statement());
  }


  LoadContextField(context_register(), Context::PREVIOUS_INDEX);

  StoreToFrameField(StandardFrameConstants::kContextOffset, context_register());
}
