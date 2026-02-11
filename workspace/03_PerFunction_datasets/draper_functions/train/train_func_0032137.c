CallCode(Handle<Code> code,
                        RelocInfo::Mode mode,
                        LInstruction* instr) {
  ASSERT(instr != NULL);
  LPointerMap* pointers = instr->pointer_map();
  RecordPosition(pointers->position());
  __ call(code, mode);
  RegisterLazyDeoptimization(instr);


  if (code->kind() == Code::TYPE_RECORDING_BINARY_OP_IC ||
      code->kind() == Code::COMPARE_IC) {
    __ nop();
  }
}
