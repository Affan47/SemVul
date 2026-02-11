AllocateJSArray() {
  JSFunction* array_function =
      Top::context()->global_context()->array_function();
  Object* result;
  { MaybeObject* maybe_result = Heap::AllocateJSObject(array_function);
    if (!maybe_result->ToObject(&result)) return maybe_result;
  }
  return result;
}
