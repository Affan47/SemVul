Clear(Address address, Code* target) {
  if (target->ic_state() == UNINITIALIZED) return;


  ClearInlinedVersion(address);
  SetTargetAtAddress(address, initialize_stub());
}
