MakeWeak(i::Object** object, void* parameters,
                  WeakReferenceCallback callback) {
  i::Isolate* isolate = i::Isolate::Current();
  LOG_API(isolate, "MakeWeak");
  isolate->global_handles()->MakeWeak(object, parameters,
                                                    callback);
}
