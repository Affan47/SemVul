SetClassName(Handle<String> name) {
  i::Isolate* isolate = Utils::OpenHandle(this)->GetIsolate();
  if (IsDeadCheck(isolate, "v8::FunctionTemplate::SetClassName()")) return;
  ENTER_V8(isolate);
  Utils::OpenHandle(this)->set_class_name(*Utils::OpenHandle(*name));
}
