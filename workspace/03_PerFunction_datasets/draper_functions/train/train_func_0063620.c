GetIndexedPropertiesExternalArrayDataLength() {
  i::Handle<i::JSObject> self = Utils::OpenHandle(this);
  ON_BAILOUT(self->GetIsolate(),
             "v8::GetIndexedPropertiesExternalArrayDataLength()",
             return 0);
  if (self->HasExternalArrayElements()) {
    return i::ExternalArray::cast(self->elements())->length();
  } else {
    return -1;
  }
}
