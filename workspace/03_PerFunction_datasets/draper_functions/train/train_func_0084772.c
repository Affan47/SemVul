ClearMirrorCache() {
  PostponeInterruptsScope postpone;
  HandleScope scope;
  ASSERT(Top::context() == *Debug::debug_context());


  Handle<String> function_name =
      Factory::LookupSymbol(CStrVector("ClearMirrorCache"));
  Handle<Object> fun(Top::global()->GetPropertyNoExceptionThrown(
      *function_name));
  ASSERT(fun->IsJSFunction());
  bool caught_exception;
  Handle<Object> js_object = Execution::TryCall(
      Handle<JSFunction>::cast(fun),
      Handle<JSObject>(Debug::debug_context()->global()),
      0, NULL, &caught_exception);
}
