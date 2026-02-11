MergeFrom(const EnumOptions& from) {
  GOOGLE_CHECK_NE(&from, this);
  uninterpreted_option_.MergeFrom(from.uninterpreted_option_);
  _extensions_.MergeFrom(from._extensions_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}
