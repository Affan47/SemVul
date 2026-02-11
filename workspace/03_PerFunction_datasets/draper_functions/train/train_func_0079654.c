Write(FixedArray* output) {
  if (sign_ != kNone) {
    if (hour_ == kNone) hour_ = 0;
    if (minute_ == kNone) minute_ = 0;
    int total_seconds = sign_ * (hour_ * 3600 + minute_ * 60);
    if (!Smi::IsValid(total_seconds)) return false;
    output->set(UTC_OFFSET, Smi::FromInt(total_seconds));
  } else {
    output->set_null(UTC_OFFSET);
  }
  return true;
}
