IsDeadCheck(i::Isolate* isolate, const char* location) {
  return !isolate->IsInitialized()
      && i::V8::IsDead() ? ReportV8Dead(location) : false;
}
