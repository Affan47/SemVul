SetSecurityToken(Handle<Value> token) {
  i::Isolate* isolate = i::Isolate::Current();
  if (IsDeadCheck(isolate, "v8::Context::SetSecurityToken()")) {
    return;
  }
  ENTER_V8(isolate);
  i::Handle<i::Context> env = Utils::OpenHandle(this);
  i::Handle<i::Object> token_handle = Utils::OpenHandle(*token);
  env->set_security_token(*token_handle);
}
