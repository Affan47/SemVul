LoadFunction(State state,
                                      Code::ExtraICState extra_ic_state,
                                      Handle<Object> object,
                                      Handle<String> name) {


  if (object->IsUndefined() || object->IsNull()) {
    return TypeError("non_object_property_call", object, name);
  }


  uint32_t index;
  if (name->AsArrayIndex(&index)) {
    Object* result;
    { MaybeObject* maybe_result = object->GetElement(index);
      if (!maybe_result->ToObject(&result)) return maybe_result;
    }

    if (result->IsJSFunction()) return result;


    result = TryCallAsFunction(result);
    if (result->IsJSFunction()) return result;


  }


  LookupResult lookup;
  LookupForRead(*object, *name, &lookup);

  if (!lookup.IsProperty()) {


    if (IsContextual(object)) {
      return ReferenceError("not_defined", name);
    }
    return TypeError("undefined_method", object, name);
  }


  if (FLAG_use_ic) {
    UpdateCaches(&lookup, state, extra_ic_state, object, name);
  }


  PropertyAttributes attr;
  Object* result;
  { MaybeObject* maybe_result =
        object->GetProperty(*object, &lookup, *name, &attr);
    if (!maybe_result->ToObject(&result)) return maybe_result;
  }

  if (lookup.type() == INTERCEPTOR) {


    if (attr == ABSENT) {
      if (IsContextual(object)) {
        return ReferenceError("not_defined", name);
      }
      return TypeError("undefined_method", object, name);
    }
  }

  ASSERT(!result->IsTheHole());

  HandleScope scope(isolate());


  Handle<Object> result_handle(result);


  ReceiverToObjectIfRequired(result_handle, object);

  if (result_handle->IsJSFunction()) {
#ifdef ENABLE_DEBUGGER_SUPPORT

    Debug* debug = isolate()->debug();
    if (debug->StepInActive()) {


      Handle<JSFunction> function(JSFunction::cast(*result_handle), isolate());
      debug->HandleStepIn(function, object, fp(), false);
      return *function;
    }
#endif

    return *result_handle;
  }


  result_handle = Handle<Object>(TryCallAsFunction(*result_handle));
  if (result_handle->IsJSFunction()) return *result_handle;

  return TypeError("property_not_function", object, name);
}
