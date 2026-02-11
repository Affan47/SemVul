HasRealNamedCallbackProperty(Handle<String> key) {
  ON_BAILOUT("v8::Object::HasRealNamedCallbackProperty()", return false);
  ENTER_V8;
  return Utils::OpenHandle(this)->HasRealNamedCallbackProperty(
      *Utils::OpenHandle(*key));
}
