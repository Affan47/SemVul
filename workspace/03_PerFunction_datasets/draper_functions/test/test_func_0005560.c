Interrupt() {
  ExecutionAccess access;
  thread_local_.interrupt_flags_ |= INTERRUPT;
  set_interrupt_limits(access);
}
