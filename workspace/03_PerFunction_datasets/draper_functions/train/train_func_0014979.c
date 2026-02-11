IsJSArrayFastElementMovingAllowed(Heap* heap,
                                                     JSArray* receiver) {
  Context* global_context = heap->isolate()->context()->global_context();
  JSObject* array_proto =
      JSObject::cast(global_context->array_function()->prototype());
  return receiver->GetPrototype() == array_proto &&
         ArrayPrototypeHasNoElements(heap, global_context, array_proto);
}
