MergeFrom(const UninterpretedOption& from) {
  GOOGLE_CHECK_NE(&from, this);
  name_.MergeFrom(from.name_);
  if (from._has_bits_[1 / 32] & (0xffu << (1 % 32))) {
    if (from.has_identifier_value()) {
      set_identifier_value(from.identifier_value());
    }
    if (from.has_positive_int_value()) {
      set_positive_int_value(from.positive_int_value());
    }
    if (from.has_negative_int_value()) {
      set_negative_int_value(from.negative_int_value());
    }
    if (from.has_double_value()) {
      set_double_value(from.double_value());
    }
    if (from.has_string_value()) {
      set_string_value(from.string_value());
    }
    if (from.has_aggregate_value()) {
      set_aggregate_value(from.aggregate_value());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}
