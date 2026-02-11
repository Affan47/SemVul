HasElementWithInterceptor(JSObject* receiver, uint32_t index) {


  AssertNoContextChange ncc;
  HandleScope scope;
  Handle<InterceptorInfo> interceptor(GetIndexedInterceptor());
  Handle<JSObject> receiver_handle(receiver);
  Handle<JSObject> holder_handle(this);
  CustomArguments args(interceptor->data(), receiver, this);
  v8::AccessorInfo info(args.end());
  if (!interceptor->query()->IsUndefined()) {
    v8::IndexedPropertyQuery query =
        v8::ToCData<v8::IndexedPropertyQuery>(interceptor->query());
    LOG(ApiIndexedPropertyAccess("interceptor-indexed-has", this, index));
    v8::Handle<v8::Integer> result;
    {

      VMState state(EXTERNAL);
      result = query(index, info);
    }
    if (!result.IsEmpty()) {
      ASSERT(result->IsInt32());
      return true;
    }
  } else if (!interceptor->getter()->IsUndefined()) {
    v8::IndexedPropertyGetter getter =
        v8::ToCData<v8::IndexedPropertyGetter>(interceptor->getter());
    LOG(ApiIndexedPropertyAccess("interceptor-indexed-has-get", this, index));
    v8::Handle<v8::Value> result;
    {

      VMState state(EXTERNAL);
      result = getter(index, info);
    }
    if (!result.IsEmpty()) return true;
  }
  return holder_handle->HasElementPostInterceptor(*receiver_handle, index);
}
