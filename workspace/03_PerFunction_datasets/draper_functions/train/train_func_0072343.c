GetIndexedPropertiesExternalArrayData() {
  ON_BAILOUT("v8::GetIndexedPropertiesExternalArrayData()", return NULL);
  i::Handle<i::JSObject> self = Utils::OpenHandle(this);
  if (self->HasExternalArrayElements()) {
    return i::ExternalArray::cast(self->elements())->external_pointer();
  } else {
    return NULL;
  }
}
