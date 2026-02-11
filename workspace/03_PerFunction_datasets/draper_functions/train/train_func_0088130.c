DebugCommand() {
  if (FLAG_debugger_auto_break) {
    ExecutionAccess access;
    thread_local_.interrupt_flags_ |= DEBUGCOMMAND;
    set_limits(kInterruptLimit, access);
  }
}
