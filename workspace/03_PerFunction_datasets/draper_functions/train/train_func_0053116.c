GetIdentityHash() {
  i::Isolate* isolate = Utils::OpenHandle(this)->GetIsolate();
  ON_BAILOUT(isolate, "v8::Object::GetIdentityHash()", return 0);
  ENTER_V8(isolate);
  i::HandleScope scope(isolate);
  i::Handle<i::JSObject> self = Utils::OpenHandle(this);
  return i::GetIdentityHash(self);
}
