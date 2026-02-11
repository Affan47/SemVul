EmitCallFunction(ZoneList<Expression*>* args) {
  ASSERT(args->length() >= 2);

  int arg_count = args->length() - 2;
  VisitForStackValue(args->at(0));
  for (int i = 0; i < arg_count; i++) {
    VisitForStackValue(args->at(i + 1));
  }
  VisitForAccumulatorValue(args->at(arg_count + 1));


  if (!result_register().is(rdi)) __ movq(rdi, result_register());
  ParameterCount count(arg_count);
  __ InvokeFunction(rdi, count, CALL_FUNCTION);
  __ movq(rsi, Operand(rbp, StandardFrameConstants::kContextOffset));
  context()->Plug(rax);
}
