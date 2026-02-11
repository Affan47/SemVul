Continue(InterruptFlag after_what) {
  ExecutionAccess access;
  thread_local_.interrupt_flags_ &= ~static_cast<int>(after_what);
  if (thread_local_.interrupt_flags_ == 0) {
    reset_limits(access);
  }
}
