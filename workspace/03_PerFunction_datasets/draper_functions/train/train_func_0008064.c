ClearMirrorCache() {
  PostponeInterruptsScope postpone(isolate_);
  HandleScope scope(isolate_);
  ASSERT(isolate_->context() == *Debug::debug_context());


  Handle<String> function_name =
      isolate_->factory()->LookupSymbol(CStrVector("ClearMirrorCache"));
  Handle<Object> fun(Isolate::Current()->global()->GetPropertyNoExceptionThrown(
      *function_name));
  ASSERT(fun->IsJSFunction());
  bool caught_exception;
  Execution::TryCall(Handle<JSFunction>::cast(fun),
      Handle<JSObject>(Debug::debug_context()->global()),
      0, NULL, &caught_exception);
}
