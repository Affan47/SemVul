Set(v8::Handle<String> name, v8::Handle<Data> value,
                   v8::PropertyAttribute attribute) {
  i::Isolate* isolate = i::Isolate::Current();
  if (IsDeadCheck(isolate, "v8::Template::Set()")) return;
  ENTER_V8(isolate);
  i::HandleScope scope(isolate);
  i::Handle<i::Object> list(Utils::OpenHandle(this)->property_list());
  if (list->IsUndefined()) {
    list = NeanderArray().value();
    Utils::OpenHandle(this)->set_property_list(*list);
  }
  NeanderArray array(list);
  array.add(Utils::OpenHandle(*name));
  array.add(Utils::OpenHandle(*value));
  array.add(Utils::OpenHandle(*v8::Integer::New(attribute)));
}
