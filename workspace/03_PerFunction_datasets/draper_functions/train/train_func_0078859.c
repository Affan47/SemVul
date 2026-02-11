NewExternal(
      v8::String::ExternalStringResource* resource) {
  EnsureInitialized("v8::String::NewExternal()");
  LOG_API("String::NewExternal");
  ENTER_V8;
  i::Handle<i::String> result = NewExternalStringHandle(resource);
  i::ExternalStringTable::AddString(*result);
  return Utils::ToLocal(result);
}
