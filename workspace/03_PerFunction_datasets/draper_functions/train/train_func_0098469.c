BackgroundCall() {
  MutexLock l(&mutex_);
  assert(bg_compaction_scheduled_);
  if (shutting_down_.Acquire_Load()) {

  } else if (!bg_error_.ok()) {

  } else {
    BackgroundCompaction();
  }

  bg_compaction_scheduled_ = false;


  MaybeScheduleCompaction();
  bg_cv_.SignalAll();
}
