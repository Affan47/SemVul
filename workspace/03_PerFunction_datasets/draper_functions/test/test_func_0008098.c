getSize() const {
  if (Parent->IsThin) {
    ErrorOr<uint32_t> Size = getHeader()->getSize();
    if (std::error_code EC = Size.getError())
      return EC;
    return Size.get();
  }
  return Data.size() - StartOfFile;
}
