CompileScriptForTracker(Handle<Script> script) {

  PostponeInterruptsScope postpone;


  CompilationInfo info(script);
  info.MarkAsGlobal();
  if (ParserApi::Parse(&info)) {

    LiveEditFunctionTracker tracker(info.function());
    if (Compiler::MakeCodeForLiveEdit(&info)) {
      ASSERT(!info.code().is_null());
      tracker.RecordRootFunctionInfo(info.code());
    } else {
      Top::StackOverflow();
    }
  }
}
