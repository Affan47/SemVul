SetElementWithCallback(Object* structure,
                                              uint32_t index,
                                              Object* value,
                                              JSObject* holder) {
  HandleScope scope;


  ASSERT(!value->IsTheHole());
  Handle<Object> value_handle(value);


  ASSERT(!structure->IsProxy());

  if (structure->IsAccessorInfo()) {

    AccessorInfo* data = AccessorInfo::cast(structure);
    Object* call_obj = data->setter();
    v8::AccessorSetter call_fun = v8::ToCData<v8::AccessorSetter>(call_obj);
    if (call_fun == NULL) return value;
    Handle<Object> number = Factory::NewNumberFromUint(index);
    Handle<String> key(Factory::NumberToString(number));
    LOG(ApiNamedPropertyAccess("store", this, *key));
    CustomArguments args(data->data(), this, JSObject::cast(holder));
    v8::AccessorInfo info(args.end());
    {

      VMState state(EXTERNAL);
      call_fun(v8::Utils::ToLocal(key),
               v8::Utils::ToLocal(value_handle),
               info);
    }
    RETURN_IF_SCHEDULED_EXCEPTION();
    return *value_handle;
  }

  if (structure->IsFixedArray()) {
    Object* setter = FixedArray::cast(structure)->get(kSetterIndex);
    if (setter->IsJSFunction()) {
     return SetPropertyWithDefinedSetter(JSFunction::cast(setter), value);
    } else {
      Handle<Object> holder_handle(holder);
      Handle<Object> key(Factory::NewNumberFromUint(index));
      Handle<Object> args[2] = { key, holder_handle };
      return Top::Throw(*Factory::NewTypeError("no_setter_in_callback",
                                               HandleVector(args, 2)));
    }
  }

  UNREACHABLE();
  return NULL;
}
