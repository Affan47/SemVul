SetData(v8::Handle<String> data) {
  i::Handle<i::Context> env = Utils::OpenHandle(this);
  i::Isolate* isolate = env->GetIsolate();
  if (IsDeadCheck(isolate, "v8::Context::SetData()")) return;
  i::Handle<i::Object> raw_data = Utils::OpenHandle(*data);
  ASSERT(env->IsGlobalContext());
  if (env->IsGlobalContext()) {
    env->set_data(*raw_data);
  }
}
