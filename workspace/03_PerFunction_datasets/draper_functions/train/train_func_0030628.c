AddObjectGroup(Persistent<Value>* objects,
                        size_t length,
                        RetainedObjectInfo* info) {
  i::Isolate* isolate = i::Isolate::Current();
  if (IsDeadCheck(isolate, "v8::V8::AddObjectGroup()")) return;
  STATIC_ASSERT(sizeof(Persistent<Value>) == sizeof(i::Object**));
  isolate->global_handles()->AddObjectGroup(
      reinterpret_cast<i::Object***>(objects), length, info);
}
