SetAresErrno(int errorno) {
  HandleScope scope;
  Handle<Value> key = String::NewSymbol("errno");
  Handle<Value> value = String::NewSymbol(AresErrnoString(errorno));
  Context::GetCurrent()->Global()->Set(key, value);
}
