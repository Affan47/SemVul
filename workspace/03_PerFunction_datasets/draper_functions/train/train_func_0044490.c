SetPointerInInternalField(int index, void* value) {
  i::Isolate* isolate = Utils::OpenHandle(this)->GetIsolate();
  ENTER_V8(isolate);
  if (CanBeEncodedAsSmi(value)) {
    Utils::OpenHandle(this)->SetInternalField(index, EncodeAsSmi(value));
  } else {
    HandleScope scope;
    i::Handle<i::Foreign> foreign =
        isolate->factory()->NewForeign(
            reinterpret_cast<i::Address>(value), i::TENURED);
    if (!foreign.is_null())
        Utils::OpenHandle(this)->SetInternalField(index, *foreign);
  }
  ASSERT_EQ(value, GetPointerFromInternalField(index));
}
