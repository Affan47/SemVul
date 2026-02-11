OnAfterCompile(Handle<Script> script,
                              AfterCompileFlags after_compile_flags) {
  HandleScope scope;


  Debug::AddScriptToScriptCache(script);


  if (!IsDebuggerActive()) return;


  if (compiling_natives()) return;


  bool in_debugger = Debug::InDebugger();


  EnterDebugger debugger;
  if (debugger.FailedToEnter()) return;


  Handle<String> update_script_break_points_symbol =
      Factory::LookupAsciiSymbol("UpdateScriptBreakPoints");
  Handle<Object> update_script_break_points =
      Handle<Object>(Debug::debug_context()->global()->
          GetPropertyNoExceptionThrown(*update_script_break_points_symbol));
  if (!update_script_break_points->IsJSFunction()) {
    return;
  }
  ASSERT(update_script_break_points->IsJSFunction());


  Handle<JSValue> wrapper = GetScriptWrapper(script);


  bool caught_exception = false;
  const int argc = 1;
  Object** argv[argc] = { reinterpret_cast<Object**>(wrapper.location()) };
  Handle<Object> result = Execution::TryCall(
      Handle<JSFunction>::cast(update_script_break_points),
      Top::builtins(), argc, argv,
      &caught_exception);
  if (caught_exception) {
    return;
  }

  if (in_debugger && (after_compile_flags & SEND_WHEN_DEBUGGING) == 0) return;
  if (!Debugger::EventActive(v8::AfterCompile)) return;


  Handle<Object> event_data = MakeCompileEvent(script,
                                               false,
                                               &caught_exception);

  if (caught_exception) {
    return;
  }

  ProcessDebugEvent(v8::AfterCompile,
                    Handle<JSObject>::cast(event_data),
                    true);
}
