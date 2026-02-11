SpaceUsedExcludingSelf() const {
  if (fields_ == NULL) return 0;

  int total_size = sizeof(*fields_) + sizeof(UnknownField) * fields_->size();
  for (int i = 0; i < fields_->size(); i++) {
    const UnknownField& field = (*fields_)[i];
    switch (field.type()) {
      case UnknownField::TYPE_LENGTH_DELIMITED:
        total_size += sizeof(*field.length_delimited_) +
          internal::StringSpaceUsedExcludingSelf(*field.length_delimited_);
        break;
      case UnknownField::TYPE_GROUP:
        total_size += field.group_->SpaceUsed();
        break;
      default:
        break;
    }
  }
  return total_size;
}
