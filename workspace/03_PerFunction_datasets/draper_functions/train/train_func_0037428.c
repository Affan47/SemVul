TestHeapLeakCheckerDeathInverse() {
  void* bar = AllocHidden(250 * sizeof(int));
  Use(&bar);
  LogHidden("Pre leaking", bar);
  Pause();
  HeapLeakChecker check("death_inverse");
  void* foo = AllocHidden(100 * sizeof(int));
  Use(&foo);
  LogHidden("Leaking", foo);
  DeAllocHidden(&bar);
  Pause();
  VerifyLeaks(&check, SAME_HEAP,
              100 * static_cast<int64>(sizeof(int)),
              1);
  DeAllocHidden(&foo);
}
