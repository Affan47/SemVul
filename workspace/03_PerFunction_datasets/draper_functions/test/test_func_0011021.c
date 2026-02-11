Set(v8::Handle<Value> key, v8::Handle<Value> value,
                     v8::PropertyAttribute attribs) {
  ON_BAILOUT("v8::Object::Set()", return false);
  ENTER_V8;
  HandleScope scope;
  i::Handle<i::Object> self = Utils::OpenHandle(this);
  i::Handle<i::Object> key_obj = Utils::OpenHandle(*key);
  i::Handle<i::Object> value_obj = Utils::OpenHandle(*value);
  EXCEPTION_PREAMBLE();
  i::Handle<i::Object> obj = i::SetProperty(
      self,
      key_obj,
      value_obj,
      static_cast<PropertyAttributes>(attribs),
      i::kNonStrictMode);
  has_pending_exception = obj.is_null();
  EXCEPTION_BAILOUT_CHECK(false);
  return true;
}
