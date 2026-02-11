HasIndexedPropertiesInPixelData() {
  i::Handle<i::JSObject> self = Utils::OpenHandle(this);
  ON_BAILOUT(self->GetIsolate(), "v8::HasIndexedPropertiesInPixelData()",
             return false);
  return self->HasExternalPixelElements();
}
