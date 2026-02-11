DefaultFatalErrorHandler(const char* location,
                                     const char* message) {
  i::VMState __state__(i::Isolate::Current(), i::OTHER);
  API_Fatal(location, message);
}
