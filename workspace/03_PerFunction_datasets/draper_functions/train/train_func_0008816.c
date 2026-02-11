AllocateStackSlot(Variable* var) {
  var->set_rewrite(new Slot(var, Slot::LOCAL, num_stack_slots_++));
}
