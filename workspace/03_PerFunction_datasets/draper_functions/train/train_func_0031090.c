DoIn(LIn* instr) {
  LOperand* obj = instr->object();
  LOperand* key = instr->key();
  EmitPushTaggedOperand(key);
  EmitPushTaggedOperand(obj);
  ASSERT(instr->HasPointerMap() && instr->HasDeoptimizationEnvironment());
  LPointerMap* pointers = instr->pointer_map();
  LEnvironment* env = instr->deoptimization_environment();
  RecordPosition(pointers->position());
  RegisterEnvironmentForDeoptimization(env);


  SafepointGenerator safepoint_generator(this,
                                         pointers,
                                         env->deoptimization_index());
  __ InvokeBuiltin(Builtins::IN, CALL_FUNCTION, safepoint_generator);
}
