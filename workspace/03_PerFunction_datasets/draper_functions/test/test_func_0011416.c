Reset() {
  SpinLockHolder cl(&control_lock_);
  DisableHandler();
  {
    SpinLockHolder sl(&signal_lock_);
    CallbackIterator it = callbacks_.begin();
    while (it != callbacks_.end()) {
      CallbackIterator tmp = it;
      ++it;
      delete *tmp;
      callbacks_.erase(tmp);
    }
  }
  callback_count_ = 0;
  if (timer_sharing_ == TIMERS_SHARED) {
    StopTimer();
  }
  timer_sharing_ = TIMERS_UNTOUCHED;
}
