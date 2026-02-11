GlobalIfNotShadowedByEval(Handle<String> name) {
  Context* context = this;


  while (!context->IsGlobalContext()) {

    if (context->has_extension()) return false;


    ASSERT(context->is_function_context());


    Handle<SerializedScopeInfo> scope_info(
        context->closure()->shared()->scope_info());
    Variable::Mode mode;
    int index = scope_info->ContextSlotIndex(*name, &mode);
    ASSERT(index < 0 || index >= MIN_CONTEXT_SLOTS);
    if (index >= 0) return false;


    int param_index = scope_info->ParameterIndex(*name);
    if (param_index >= 0) return false;


    index = scope_info->FunctionContextSlotIndex(*name);
    if (index >= 0) return false;
    context = Context::cast(context->closure()->context());
  }


  return true;
}
