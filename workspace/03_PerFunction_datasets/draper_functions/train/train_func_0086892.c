GetNativeFunction(
    v8::Handle<v8::String> str) {
  if (strcmp(*v8::String::AsciiValue(str), "externalizeString") == 0) {
    return v8::FunctionTemplate::New(ExternalizeStringExtension::Externalize);
  } else {
    ASSERT(strcmp(*v8::String::AsciiValue(str), "isAsciiString") == 0);
    return v8::FunctionTemplate::New(ExternalizeStringExtension::IsAscii);
  }
}
