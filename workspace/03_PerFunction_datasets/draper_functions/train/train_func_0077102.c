GetEndColumn() const {
  if (IsDeadCheck("v8::Message::GetEndColumn()")) return 0;
  ENTER_V8;
  HandleScope scope;
  i::Handle<i::JSObject> data_obj = Utils::OpenHandle(this);
  EXCEPTION_PREAMBLE();
  i::Handle<i::Object> start_col_obj = CallV8HeapFunction(
      "GetPositionInLine",
      data_obj,
      &has_pending_exception);
  EXCEPTION_BAILOUT_CHECK(0);
  int start = static_cast<int>(GetProperty(data_obj, "startPos")->Number());
  int end = static_cast<int>(GetProperty(data_obj, "endPos")->Number());
  return static_cast<int>(start_col_obj->Number()) + (end - start);
}
