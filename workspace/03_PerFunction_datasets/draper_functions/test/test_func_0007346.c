Delete(uint32_t index) {
  ON_BAILOUT("v8::Object::DeleteProperty()", return false);
  ENTER_V8;
  HandleScope scope;
  i::Handle<i::JSObject> self = Utils::OpenHandle(this);
  return i::DeleteElement(self, index)->IsTrue();
}
