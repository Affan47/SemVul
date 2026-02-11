Store(State state,
                            StrictModeFlag strict_mode,
                            Handle<Object> object,
                            Handle<String> name,
                            Handle<Object> value) {


  if (object->IsUndefined() || object->IsNull()) {
    return TypeError("non_object_property_store", object, name);
  }

  if (!object->IsJSReceiver()) {

    if (strict_mode == kStrictMode && object->IsString() &&
        name->Equals(isolate()->heap()->length_symbol())) {
      return TypeError("strict_read_only_property", object, name);
    }

    return *value;
  }


  if (object->IsJSProxy()) {
    return JSReceiver::cast(*object)->
        SetProperty(*name, *value, NONE, strict_mode);
  }

  Handle<JSObject> receiver = Handle<JSObject>::cast(object);


  uint32_t index;
  if (name->AsArrayIndex(&index)) {
    HandleScope scope(isolate());
    Handle<Object> result = SetElement(receiver, index, value, strict_mode);
    if (result.is_null()) return Failure::Exception();
    return *value;
  }


  if (receiver->IsJSArray()
      && name->Equals(isolate()->heap()->length_symbol())
      && JSArray::cast(*receiver)->AllowsSetElementsLength()) {
#ifdef DEBUG
    if (FLAG_trace_ic) PrintF("[StoreIC : +#length /array]\n");
#endif
    Builtins::Name target = (strict_mode == kStrictMode)
        ? Builtins::kStoreIC_ArrayLength_Strict
        : Builtins::kStoreIC_ArrayLength;
    set_target(isolate()->builtins()->builtin(target));
    return receiver->SetProperty(*name, *value, NONE, strict_mode);
  }


  if (FLAG_use_ic && !receiver->IsJSGlobalProxy()) {
    LookupResult lookup;

    if (LookupForWrite(*receiver, *name, &lookup)) {

      UpdateCaches(&lookup, state, strict_mode, receiver, name, value);
    } else {


      if (strict_mode == kStrictMode) {
        if (lookup.IsFound() && lookup.IsReadOnly()) {
          return TypeError("strict_read_only_property", object, name);
        } else if (IsContextual(object)) {
          return ReferenceError("not_defined", name);
        }
      }
    }
  }

  if (receiver->IsJSGlobalProxy()) {


    Code* stub = (strict_mode == kStrictMode)
        ? global_proxy_stub_strict()
        : global_proxy_stub();
    if (target() != stub) {
      set_target(stub);
#ifdef DEBUG
      TraceIC("StoreIC", name, state, target());
#endif
    }
  }


  return receiver->SetProperty(*name, *value, NONE, strict_mode);
}
