NewFunctionFromSharedFunctionInfo(
    Handle<SharedFunctionInfo> function_info,
    Handle<Context> context,
    PretenureFlag pretenure) {
  Handle<JSFunction> result = BaseNewFunctionFromSharedFunctionInfo(
      function_info,
      function_info->strict_mode()
          ? isolate()->strict_mode_function_map()
          : isolate()->function_map(),
      pretenure);

  result->set_context(*context);
  int number_of_literals = function_info->num_literals();
  Handle<FixedArray> literals = NewFixedArray(number_of_literals, pretenure);
  if (number_of_literals > 0) {


    literals->set(JSFunction::kLiteralGlobalContextIndex,
                  context->global_context());
  }
  result->set_literals(*literals);
  result->set_next_function_link(isolate()->heap()->undefined_value());

  if (V8::UseCrankshaft() &&
      FLAG_always_opt &&
      result->is_compiled() &&
      !function_info->is_toplevel() &&
      function_info->allows_lazy_compilation()) {
    result->MarkForLazyRecompilation();
  }
  return result;
}
