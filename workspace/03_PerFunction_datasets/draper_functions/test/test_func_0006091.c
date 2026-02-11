MayIndexedAccess(JSObject* receiver,
                               uint32_t index,
                               v8::AccessType type) {
  ASSERT(receiver->IsAccessCheckNeeded());


  ASSERT(context());

  MayAccessDecision decision = MayAccessPreCheck(this, receiver, type);
  if (decision != UNKNOWN) return decision == YES;


  JSFunction* constructor = JSFunction::cast(receiver->map()->constructor());
  if (!constructor->shared()->IsApiFunction()) return false;

  Object* data_obj =
      constructor->shared()->get_api_func_data()->access_check_info();
  if (data_obj == heap_.undefined_value()) return false;

  Object* fun_obj = AccessCheckInfo::cast(data_obj)->indexed_callback();
  v8::IndexedSecurityCallback callback =
      v8::ToCData<v8::IndexedSecurityCallback>(fun_obj);

  if (!callback) return false;

  HandleScope scope(this);
  Handle<JSObject> receiver_handle(receiver, this);
  Handle<Object> data(AccessCheckInfo::cast(data_obj)->data(), this);
  LOG(this, ApiIndexedSecurityCheck(index));
  bool result = false;
  {

    VMState state(this, EXTERNAL);
    result = callback(v8::Utils::ToLocal(receiver_handle),
                      index,
                      type,
                      v8::Utils::ToLocal(data));
  }
  return result;
}
