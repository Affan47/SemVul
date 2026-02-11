IdleNotification() {
  static const int kIdlesBeforeScavenge = 4;
  static const int kIdlesBeforeMarkSweep = 7;
  static const int kIdlesBeforeMarkCompact = 8;
  static int number_idle_notifications = 0;
  static int last_gc_count = gc_count_;

  bool uncommit = true;
  bool finished = false;

  if (last_gc_count == gc_count_) {
    number_idle_notifications++;
  } else {
    number_idle_notifications = 0;
    last_gc_count = gc_count_;
  }

  if (number_idle_notifications == kIdlesBeforeScavenge) {
    if (contexts_disposed_ > 0) {
      HistogramTimerScope scope(&Counters::gc_context);
      CollectAllGarbage(false);
    } else {
      CollectGarbage(0, NEW_SPACE);
    }
    new_space_.Shrink();
    last_gc_count = gc_count_;

  } else if (number_idle_notifications == kIdlesBeforeMarkSweep) {


    CompilationCache::Clear();

    CollectAllGarbage(false);
    new_space_.Shrink();
    last_gc_count = gc_count_;

  } else if (number_idle_notifications == kIdlesBeforeMarkCompact) {
    CollectAllGarbage(true);
    new_space_.Shrink();
    last_gc_count = gc_count_;
    number_idle_notifications = 0;
    finished = true;

  } else if (contexts_disposed_ > 0) {
    if (FLAG_expose_gc) {
      contexts_disposed_ = 0;
    } else {
      HistogramTimerScope scope(&Counters::gc_context);
      CollectAllGarbage(false);
      last_gc_count = gc_count_;
    }


    if (number_idle_notifications <= 1) {
      number_idle_notifications = 0;
      uncommit = false;
    }
  }


  ASSERT(contexts_disposed_ == 0);
  if (uncommit) Heap::UncommitFromSpace();
  return finished;
}
