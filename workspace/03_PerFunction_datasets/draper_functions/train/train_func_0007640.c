getCStr(uint32_t *offset_ptr) const {
  uint32_t offset = *offset_ptr;
  StringRef::size_type pos = Data.find('\0', offset);
  if (pos != StringRef::npos) {
    *offset_ptr = pos + 1;
    return Data.data() + offset;
  }
  return nullptr;
}
