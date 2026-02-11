CallCodeGeneric(Handle<Code> code,
                               RelocInfo::Mode mode,
                               LInstruction* instr,
                               SafepointMode safepoint_mode,
                               int argc) {
  EnsureSpaceForLazyDeopt(Deoptimizer::patch_size() - masm()->CallSize(code));
  ASSERT(instr != NULL);
  LPointerMap* pointers = instr->pointer_map();
  RecordPosition(pointers->position());
  __ call(code, mode);
  RecordSafepointWithLazyDeopt(instr, safepoint_mode, argc);


  if (code->kind() == Code::BINARY_OP_IC ||
      code->kind() == Code::COMPARE_IC) {
    __ nop();
  }
}
