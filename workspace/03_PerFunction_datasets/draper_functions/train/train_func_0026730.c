Has(v8::Handle<String> key) {
  i::Isolate* isolate = Utils::OpenHandle(this)->GetIsolate();
  ON_BAILOUT(isolate, "v8::Object::Has()", return false);
  ENTER_V8(isolate);
  i::Handle<i::JSObject> self = Utils::OpenHandle(this);
  i::Handle<i::String> key_obj = Utils::OpenHandle(*key);
  return self->HasProperty(*key_obj);
}
