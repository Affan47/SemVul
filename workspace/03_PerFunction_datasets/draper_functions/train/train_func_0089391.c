AllocateCatchContext(JSFunction* function,
                                        Context* previous,
                                        String* name,
                                        Object* thrown_object) {
  STATIC_ASSERT(Context::MIN_CONTEXT_SLOTS == Context::THROWN_OBJECT_INDEX);
  Object* result;
  { MaybeObject* maybe_result =
        AllocateFixedArray(Context::MIN_CONTEXT_SLOTS + 1);
    if (!maybe_result->ToObject(&result)) return maybe_result;
  }
  Context* context = reinterpret_cast<Context*>(result);
  context->set_map(catch_context_map());
  context->set_closure(function);
  context->set_previous(previous);
  context->set_extension(name);
  context->set_global(previous->global());
  context->set(Context::THROWN_OBJECT_INDEX, thrown_object);
  return context;
}
