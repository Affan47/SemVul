Clear(Address address, Code* target) {
  State state = target->ic_state();
  if (state == UNINITIALIZED) return;
  Code* code =
      StubCache::FindCallInitialize(target->arguments_count(),
                                    target->ic_in_loop(),
                                    target->kind());
  SetTargetAtAddress(address, code);
}
