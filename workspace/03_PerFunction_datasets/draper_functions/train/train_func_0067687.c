CommittedMemoryExecutable() {
  if (!HasBeenSetup()) return 0;

  return isolate()->memory_allocator()->SizeExecutable();
}
