MarkAsUndetectable() {
  if (IsDeadCheck("v8::ObjectTemplate::MarkAsUndetectable()")) return;
  ENTER_V8;
  HandleScope scope;
  EnsureConstructor(this);
  i::FunctionTemplateInfo* constructor =
      i::FunctionTemplateInfo::cast(Utils::OpenHandle(this)->constructor());
  i::Handle<i::FunctionTemplateInfo> cons(constructor);
  cons->set_undetectable(true);
}
