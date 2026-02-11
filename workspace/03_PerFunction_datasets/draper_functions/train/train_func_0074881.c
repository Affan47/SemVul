GetScriptData() const {
  if (IsDeadCheck("v8::Message::GetScriptResourceData()")) {
    return Local<Value>();
  }
  ENTER_V8;
  HandleScope scope;
  i::Handle<i::JSMessageObject> message =
      i::Handle<i::JSMessageObject>::cast(Utils::OpenHandle(this));

  i::Handle<i::JSValue> script =
      i::Handle<i::JSValue>::cast(i::Handle<i::Object>(message->script()));
  i::Handle<i::Object> data(i::Script::cast(script->value())->data());
  return scope.Close(Utils::ToLocal(data));
}
