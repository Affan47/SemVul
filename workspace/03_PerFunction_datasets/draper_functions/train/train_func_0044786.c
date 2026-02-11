AddBignum(const Bignum& other) {
  ASSERT(IsClamped());
  ASSERT(other.IsClamped());


  Align(other);


  EnsureCapacity(1 + Max(BigitLength(), other.BigitLength()) - exponent_);
  Chunk carry = 0;
  int bigit_pos = other.exponent_ - exponent_;
  ASSERT(bigit_pos >= 0);
  for (int i = 0; i < other.used_digits_; ++i) {
    Chunk sum = bigits_[bigit_pos] + other.bigits_[i] + carry;
    bigits_[bigit_pos] = sum & kBigitMask;
    carry = sum >> kBigitSize;
    bigit_pos++;
  }

  while (carry != 0) {
    Chunk sum = bigits_[bigit_pos] + carry;
    bigits_[bigit_pos] = sum & kBigitMask;
    carry = sum >> kBigitSize;
    bigit_pos++;
  }
  used_digits_ = Max(bigit_pos, used_digits_);
  ASSERT(IsClamped());
}
