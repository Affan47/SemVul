IsExternalAscii() const {
  i::Handle<i::String> str = Utils::OpenHandle(this);
  if (IsDeadCheck(str->GetIsolate(), "v8::String::IsExternalAscii()")) {
    return false;
  }
  return i::StringShape(*str).IsExternalAscii();
}
