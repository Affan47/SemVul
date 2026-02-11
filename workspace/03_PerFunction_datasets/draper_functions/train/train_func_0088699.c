MeetRegisterConstraints(HBasicBlock* block) {
  int start = block->first_instruction_index();
  int end = block->last_instruction_index();
  for (int i = start; i <= end; ++i) {
    if (IsGapAt(i)) {
      LInstruction* instr = NULL;
      LInstruction* prev_instr = NULL;
      if (i < end) instr = InstructionAt(i + 1);
      if (i > start) prev_instr = InstructionAt(i - 1);
      MeetConstraintsBetween(prev_instr, instr, i);
    }
  }
}
