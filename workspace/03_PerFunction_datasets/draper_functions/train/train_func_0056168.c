SetDebugEventListener(v8::Handle<v8::Object> that,
                                  Handle<Value> data) {
  ON_BAILOUT("v8::Debug::SetDebugEventListener()", return false);
  ENTER_V8;
  i::Debugger::SetEventListener(Utils::OpenHandle(*that),
                                Utils::OpenHandle(*data));
  return true;
}
