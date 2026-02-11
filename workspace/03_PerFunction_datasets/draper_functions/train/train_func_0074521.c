Load() {

  if (IsLoaded()) return true;


  if (Debugger::compiling_natives() || Debugger::is_loading_debugger())
    return false;
  Debugger::set_loading_debugger(true);


  DisableBreak disable(true);
  PostponeInterruptsScope postpone;


  HandleScope scope;
  Handle<Context> context =
      Bootstrapper::CreateEnvironment(Handle<Object>::null(),
                                      v8::Handle<ObjectTemplate>(),
                                      NULL);


  SaveContext save;
  Top::set_context(*context);


  Handle<String> key = Factory::LookupAsciiSymbol("builtins");
  Handle<GlobalObject> global = Handle<GlobalObject>(context->global());
  RETURN_IF_EMPTY_HANDLE_VALUE(
      SetProperty(global, key, Handle<Object>(global->builtins()),
                  NONE, kNonStrictMode),
      false);


  Debugger::set_compiling_natives(true);
  bool caught_exception =
      !CompileDebuggerScript(Natives::GetIndex("mirror")) ||
      !CompileDebuggerScript(Natives::GetIndex("debug"));

  if (FLAG_enable_liveedit) {
    caught_exception = caught_exception ||
        !CompileDebuggerScript(Natives::GetIndex("liveedit"));
  }

  Debugger::set_compiling_natives(false);


  Debugger::set_loading_debugger(false);


  if (caught_exception) return false;


  debug_context_ = context;

  return true;
}
