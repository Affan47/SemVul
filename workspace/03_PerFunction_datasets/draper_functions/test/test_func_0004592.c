TryGetConstructorDelegate(
    Handle<Object> object,
    bool* has_pending_exception) {
  ASSERT(!object->IsJSFunction());
  Isolate* isolate = Isolate::Current();


  Object* fun = *object;
  while (fun->IsJSFunctionProxy()) {
    fun = JSFunctionProxy::cast(fun)->call_trap();
  }
  if (fun->IsJSFunction()) return Handle<Object>(fun);


  if (fun->IsHeapObject() &&
      HeapObject::cast(fun)->map()->has_instance_call_handler()) {
    return Handle<JSFunction>(
        isolate->global_context()->call_as_constructor_delegate());
  }


  i::Handle<i::Object> error_obj = isolate->factory()->NewTypeError(
      "called_non_callable", i::HandleVector<i::Object>(&object, 1));
  isolate->Throw(*error_obj);
  *has_pending_exception = true;

  return isolate->factory()->undefined_value();
}
