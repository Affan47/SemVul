DeoptimizeIf(Condition cc, LEnvironment* environment) {
  RegisterEnvironmentForDeoptimization(environment);
  ASSERT(environment->HasBeenRegistered());
  int id = environment->deoptimization_index();
  Address entry = Deoptimizer::GetDeoptimizationEntry(id, Deoptimizer::EAGER);
  ASSERT(entry != NULL);
  if (entry == NULL) {
    Abort("bailout was not prepared");
    return;
  }

  if (cc == no_condition) {
    __ Jump(entry, RelocInfo::RUNTIME_ENTRY);
  } else {
    JumpTableEntry* jump_info = NULL;


    if (jump_table_.length() > 0 &&
        jump_table_[jump_table_.length() - 1]->address_ == entry) {
      jump_info = jump_table_[jump_table_.length() - 1];
    } else {
      jump_info = new JumpTableEntry(entry);
      jump_table_.Add(jump_info);
    }
    __ j(cc, &jump_info->label_);
  }
}
