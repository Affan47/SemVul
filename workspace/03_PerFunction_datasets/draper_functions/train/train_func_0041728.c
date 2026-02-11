ReattachGlobal(Handle<Object> global_object) {
  i::Isolate* isolate = i::Isolate::Current();
  if (IsDeadCheck(isolate, "v8::Context::ReattachGlobal()")) return;
  ENTER_V8(isolate);
  i::Object** ctx = reinterpret_cast<i::Object**>(this);
  i::Handle<i::Context> context =
      i::Handle<i::Context>::cast(i::Handle<i::Object>(ctx));
  isolate->bootstrapper()->ReattachGlobal(
      context,
      Utils::OpenHandle(*global_object));
}
