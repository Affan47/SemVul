CheckForInlineRuntimeCall(CallRuntime* node) {
  ZoneList<Expression*>* args = node->arguments();
  Handle<String> name = node->name();
  Runtime::Function* function = node->function();
  if (function != NULL && function->intrinsic_type == Runtime::INLINE) {
    int lookup_index = static_cast<int>(function->function_id) -
        static_cast<int>(Runtime::kFirstInlineFunction);
    ASSERT(lookup_index >= 0);
    ASSERT(static_cast<size_t>(lookup_index) <
           ARRAY_SIZE(kInlineFunctionGenerators));
    InlineFunctionGenerator generator = kInlineFunctionGenerators[lookup_index];
    (this->*generator)(args);
    return true;
  }
  return false;
}
