GetPropertyWithInterceptor(
    JSObject* receiver,
    String* name,
    PropertyAttributes* attributes) {
  InterceptorInfo* interceptor = GetNamedInterceptor();
  HandleScope scope;
  Handle<JSObject> receiver_handle(receiver);
  Handle<JSObject> holder_handle(this);
  Handle<String> name_handle(name);

  if (!interceptor->getter()->IsUndefined()) {
    v8::NamedPropertyGetter getter =
        v8::ToCData<v8::NamedPropertyGetter>(interceptor->getter());
    LOG(ApiNamedPropertyAccess("interceptor-named-get", *holder_handle, name));
    CustomArguments args(interceptor->data(), receiver, this);
    v8::AccessorInfo info(args.end());
    v8::Handle<v8::Value> result;
    {

      VMState state(EXTERNAL);
      result = getter(v8::Utils::ToLocal(name_handle), info);
    }
    RETURN_IF_SCHEDULED_EXCEPTION();
    if (!result.IsEmpty()) {
      *attributes = NONE;
      return *v8::Utils::OpenHandle(*result);
    }
  }

  MaybeObject* result = holder_handle->GetPropertyPostInterceptor(
      *receiver_handle,
      *name_handle,
      attributes);
  RETURN_IF_SCHEDULED_EXCEPTION();
  return result;
}
