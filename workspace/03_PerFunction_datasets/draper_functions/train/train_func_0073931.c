SetCallHandler(InvocationCallback callback,
                                      v8::Handle<Value> data) {
  if (IsDeadCheck("v8::FunctionTemplate::SetCallHandler()")) return;
  ENTER_V8;
  HandleScope scope;
  i::Handle<i::Struct> struct_obj =
      i::Factory::NewStruct(i::CALL_HANDLER_INFO_TYPE);
  i::Handle<i::CallHandlerInfo> obj =
      i::Handle<i::CallHandlerInfo>::cast(struct_obj);
  SET_FIELD_WRAPPED(obj, set_callback, callback);
  if (data.IsEmpty()) data = v8::Undefined();
  obj->set_data(*Utils::OpenHandle(*data));
  Utils::OpenHandle(this)->set_call_code(*obj);
}
