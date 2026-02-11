VisitCallNew(CallNew* expr) {
  Comment cmnt(masm_, "[ CallNew");


  VisitForStackValue(expr->expression());


  ZoneList<Expression*>* args = expr->arguments();
  int arg_count = args->length();
  for (int i = 0; i < arg_count; i++) {
    VisitForStackValue(args->at(i));
  }


  SetSourcePosition(expr->position());


  __ Set(rax, arg_count);
  __ movq(rdi, Operand(rsp, arg_count * kPointerSize));

  Handle<Code> construct_builtin =
      isolate()->builtins()->JSConstructCall();
  __ Call(construct_builtin, RelocInfo::CONSTRUCT_CALL);
  context()->Plug(rax);
}
