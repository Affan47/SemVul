MergeFrom(const CodeGeneratorResponse_File& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_name()) {
      set_name(from.name());
    }
    if (from.has_insertion_point()) {
      set_insertion_point(from.insertion_point());
    }
    if (from.has_content()) {
      set_content(from.content());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}
