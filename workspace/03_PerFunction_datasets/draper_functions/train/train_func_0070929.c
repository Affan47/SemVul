VisitCallRuntime(CallRuntime* expr) {
  Handle<String> name = expr->name();
  if (name->length() > 0 && name->Get(0) == '_') {
    Comment cmnt(masm_, "[ InlineRuntimeCall");
    EmitInlineRuntimeCall(expr);
    return;
  }

  Comment cmnt(masm_, "[ CallRuntime");
  ZoneList<Expression*>* args = expr->arguments();

  if (expr->is_jsruntime()) {

    __ movq(rax, GlobalObjectOperand());
    __ push(FieldOperand(rax, GlobalObject::kBuiltinsOffset));
  }


  int arg_count = args->length();
  for (int i = 0; i < arg_count; i++) {
    VisitForStackValue(args->at(i));
  }

  if (expr->is_jsruntime()) {

    __ Move(rcx, expr->name());
    RelocInfo::Mode mode = RelocInfo::CODE_TARGET;
    Handle<Code> ic =
        isolate()->stub_cache()->ComputeCallInitialize(arg_count, mode);
    __ call(ic, mode, expr->id());

    __ movq(rsi, Operand(rbp, StandardFrameConstants::kContextOffset));
  } else {
    __ CallRuntime(expr->function(), arg_count);
  }
  context()->Plug(rax);
}
