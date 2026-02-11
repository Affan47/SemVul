WriteGroupMaybeToArray(int field_number,
                                            const MessageLite& value,
                                            io::CodedOutputStream* output) {
  WriteTag(field_number, WIRETYPE_START_GROUP, output);
  const int size = value.GetCachedSize();
  uint8* target = output->GetDirectBufferForNBytesAndAdvance(size);
  if (target != NULL) {
    uint8* end = value.SerializeWithCachedSizesToArray(target);
    GOOGLE_DCHECK_EQ(end - target, size);
  } else {
    value.SerializeWithCachedSizes(output);
  }
  WriteTag(field_number, WIRETYPE_END_GROUP, output);
}
