Call(Handle<JSFunction> fun,
                              Handle<Object> data,
                              bool* pending_exception) {

  Debugger::never_unload_debugger_ = true;


  EnterDebugger debugger;
  if (debugger.FailedToEnter()) {
    return Factory::undefined_value();
  }


  bool caught_exception = false;
  Handle<Object> exec_state = MakeExecutionState(&caught_exception);
  if (caught_exception) {
    return Factory::undefined_value();
  }

  static const int kArgc = 2;
  Object** argv[kArgc] = { exec_state.location(), data.location() };
  Handle<Object> result = Execution::Call(
      fun,
      Handle<Object>(Debug::debug_context_->global_proxy()),
      kArgc,
      argv,
      pending_exception);
  return result;
}
