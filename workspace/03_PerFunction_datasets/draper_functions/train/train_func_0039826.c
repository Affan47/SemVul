New(double time) {
  i::Isolate* isolate = i::Isolate::Current();
  EnsureInitializedForIsolate(isolate, "v8::Date::New()");
  LOG_API(isolate, "Date::New");
  if (isnan(time)) {

    time = i::OS::nan_value();
  }
  ENTER_V8(isolate);
  EXCEPTION_PREAMBLE(isolate);
  i::Handle<i::Object> obj =
      i::Execution::NewDate(time, &has_pending_exception);
  EXCEPTION_BAILOUT_CHECK(isolate, Local<v8::Value>());
  return Utils::ToLocal(obj);
}
