IsFunction() const {
  if (IsDeadCheck("v8::Value::IsFunction()")) return false;
  return Utils::OpenHandle(this)->IsJSFunction();
}
