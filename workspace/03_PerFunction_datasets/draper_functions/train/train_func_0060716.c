IsValidFP(Address fp) {
  if (!validator_.IsValid(fp)) return false;
  Address sp = ExitFrame::ComputeStackPointer(fp);
  if (!validator_.IsValid(sp)) return false;
  StackFrame::State state;
  ExitFrame::FillState(fp, sp, &state);
  if (!validator_.IsValid(reinterpret_cast<Address>(state.pc_address))) {
    return false;
  }
  return *state.pc_address != NULL;
}
