GetHashField() {
  ASSERT(is_valid());
  if (length_ <= String::kMaxHashCalcLength) {
    if (is_array_index()) {
      return MakeArrayIndexHash(array_index(), length_);
    }
    return (GetHash() << String::kHashShift) | String::kIsNotArrayIndexMask;
  } else {
    return (length_ << String::kHashShift) | String::kIsNotArrayIndexMask;
  }
}
