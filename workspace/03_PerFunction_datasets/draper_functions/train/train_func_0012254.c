Serialize(OutputStream* stream,
                             HeapSnapshot::SerializationFormat format) const {
  i::Isolate* isolate = i::Isolate::Current();
  IsDeadCheck(isolate, "v8::HeapSnapshot::Serialize");
  ApiCheck(format == kJSON,
           "v8::HeapSnapshot::Serialize",
           "Unknown serialization format");
  ApiCheck(stream->GetOutputEncoding() == OutputStream::kAscii,
           "v8::HeapSnapshot::Serialize",
           "Unsupported output encoding");
  ApiCheck(stream->GetChunkSize() > 0,
           "v8::HeapSnapshot::Serialize",
           "Invalid stream chunk size");
  i::HeapSnapshotJSONSerializer serializer(ToInternal(this));
  serializer.Serialize(stream);
}
