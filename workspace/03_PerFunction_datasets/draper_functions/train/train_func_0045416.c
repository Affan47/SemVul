New() {
  EnsureInitialized("v8::Object::New()");
  LOG_API("Object::New");
  ENTER_V8;
  i::Handle<i::JSObject> obj =
      i::Factory::NewJSObject(i::Top::object_function());
  return Utils::ToLocal(obj);
}
