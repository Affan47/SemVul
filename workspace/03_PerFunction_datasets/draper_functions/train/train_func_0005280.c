RangeError(v8::Handle<v8::String> raw_message) {
  i::Isolate* isolate = i::Isolate::Current();
  LOG_API(isolate, "RangeError");
  ON_BAILOUT(isolate, "v8::Exception::RangeError()", return Local<Value>());
  ENTER_V8(isolate);
  i::Object* error;
  {
    i::HandleScope scope(isolate);
    i::Handle<i::String> message = Utils::OpenHandle(*raw_message);
    i::Handle<i::Object> result = isolate->factory()->NewRangeError(message);
    error = *result;
  }
  i::Handle<i::Object> result(error);
  return Utils::ToLocal(result);
}
