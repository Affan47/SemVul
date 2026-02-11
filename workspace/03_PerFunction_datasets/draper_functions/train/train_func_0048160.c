ConvertAndSetOverflow(int64_t result, bool* overflow) {
  if (result > kMaxInt) {
    *overflow = true;
    return kMaxInt;
  }
  if (result < kMinInt) {
    *overflow = true;
    return kMinInt;
  }
  return static_cast<int32_t>(result);
}
