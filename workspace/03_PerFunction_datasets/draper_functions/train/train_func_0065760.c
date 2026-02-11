GetLineNumber() const {
  i::Isolate* isolate = Utils::OpenHandle(this)->GetIsolate();
  ON_BAILOUT(isolate, "v8::Message::GetLineNumber()", return kNoLineNumberInfo);
  ENTER_V8(isolate);
  i::HandleScope scope(isolate);

  EXCEPTION_PREAMBLE(isolate);
  i::Handle<i::Object> result = CallV8HeapFunction("GetLineNumber",
                                                   Utils::OpenHandle(this),
                                                   &has_pending_exception);
  EXCEPTION_BAILOUT_CHECK(isolate, 0);
  return static_cast<int>(result->Number());
}
