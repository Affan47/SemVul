MarkAsCall(LInstruction* instr,
                                        HInstruction* hinstr,
                                        CanDeoptimize can_deoptimize) {
#ifdef DEBUG
  instr->VerifyCall();
#endif
  instr->MarkAsCall();
  instr = AssignPointerMap(instr);

  if (hinstr->HasSideEffects()) {
    ASSERT(hinstr->next()->IsSimulate());
    HSimulate* sim = HSimulate::cast(hinstr->next());
    instr = SetInstructionPendingDeoptimizationEnvironment(
        instr, sim->ast_id());
  }


  bool needs_environment =
      (can_deoptimize == CAN_DEOPTIMIZE_EAGERLY) || !hinstr->HasSideEffects();
  if (needs_environment && !instr->HasEnvironment()) {
    instr = AssignEnvironment(instr);
  }

  return instr;
}
