DoInvokeFunction(LInvokeFunction* instr) {
  ASSERT(ToRegister(instr->function()).is(rdi));
  ASSERT(instr->HasPointerMap());
  ASSERT(instr->HasDeoptimizationEnvironment());
  LPointerMap* pointers = instr->pointer_map();
  LEnvironment* env = instr->deoptimization_environment();
  RecordPosition(pointers->position());
  RegisterEnvironmentForDeoptimization(env);
  SafepointGenerator generator(this, pointers, env->deoptimization_index());
  ParameterCount count(instr->arity());
  __ InvokeFunction(rdi, count, CALL_FUNCTION, generator, CALL_AS_METHOD);
  __ movq(rsi, Operand(rbp, StandardFrameConstants::kContextOffset));
}
