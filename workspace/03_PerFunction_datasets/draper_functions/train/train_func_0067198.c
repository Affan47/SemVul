PreventExtensions() {
  Isolate* isolate = GetIsolate();
  if (IsAccessCheckNeeded() &&
      !isolate->MayNamedAccess(this,
                               isolate->heap()->undefined_value(),
                               v8::ACCESS_KEYS)) {
    isolate->ReportFailedAccessCheck(this, v8::ACCESS_KEYS);
    return isolate->heap()->false_value();
  }

  if (IsJSGlobalProxy()) {
    Object* proto = GetPrototype();
    if (proto->IsNull()) return this;
    ASSERT(proto->IsJSGlobalObject());
    return JSObject::cast(proto)->PreventExtensions();
  }


  if (HasExternalArrayElements()) {
    HandleScope scope(isolate);
    Handle<Object> object(this);
    Handle<Object> error  =
        isolate->factory()->NewTypeError(
            "cant_prevent_ext_external_array_elements",
            HandleVector(&object, 1));
    return isolate->Throw(*error);
  }


  SeededNumberDictionary* dictionary = NULL;
  { MaybeObject* maybe = NormalizeElements();
    if (!maybe->To<SeededNumberDictionary>(&dictionary)) return maybe;
  }
  ASSERT(HasDictionaryElements() || HasDictionaryArgumentsElements());

  dictionary->set_requires_slow_elements();


  Map* new_map;
  { MaybeObject* maybe = map()->CopyDropTransitions();
    if (!maybe->To<Map>(&new_map)) return maybe;
  }
  new_map->set_is_extensible(false);
  set_map(new_map);
  ASSERT(!map()->is_extensible());
  return new_map;
}
