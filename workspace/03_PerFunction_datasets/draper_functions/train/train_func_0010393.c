HeapLeakChecker_RunHeapCleanups() {
  if (FLAGS_heap_check == "local")
    return;
  { SpinLockHolder l(&heap_checker_lock);

    if (heap_checker_pid != getpid()) return;
  }
  HeapCleaner::RunHeapCleanups();
  if (!FLAGS_heap_check_after_destructors) HeapLeakChecker::DoMainHeapCheck();
}
