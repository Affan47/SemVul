AsArray() {
  i::Isolate* isolate = Utils::OpenHandle(this)->GetIsolate();
  if (IsDeadCheck(isolate, "v8::StackTrace::AsArray()")) Local<Array>();
  ENTER_V8(isolate);
  return Utils::ToLocal(Utils::OpenHandle(this));
}
