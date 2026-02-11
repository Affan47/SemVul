ExtractClosureReferences(JSObject* js_obj,
                                              HeapEntry* entry) {
  if (js_obj->IsJSFunction()) {
    HandleScope hs;
    JSFunction* func = JSFunction::cast(js_obj);
    Context* context = func->context();
    ZoneScope zscope(Isolate::Current(), DELETE_ON_EXIT);
    SerializedScopeInfo* serialized_scope_info =
        context->closure()->shared()->scope_info();
    ScopeInfo<ZoneListAllocationPolicy> zone_scope_info(serialized_scope_info);
    int locals_number = zone_scope_info.NumberOfLocals();
    for (int i = 0; i < locals_number; ++i) {
      String* local_name = *zone_scope_info.LocalName(i);
      int idx = serialized_scope_info->ContextSlotIndex(local_name, NULL);
      if (idx >= 0 && idx < context->length()) {
        SetClosureReference(js_obj, entry, local_name, context->get(idx));
      }
    }
  }
}
