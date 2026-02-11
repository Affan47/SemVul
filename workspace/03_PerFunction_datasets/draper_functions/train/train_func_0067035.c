DivideModuloIntBignum(const Bignum& other) {
  ASSERT(IsClamped());
  ASSERT(other.IsClamped());
  ASSERT(other.used_digits_ > 0);


  if (BigitLength() < other.BigitLength()) {
    return 0;
  }

  Align(other);

  uint16_t result = 0;


  while (BigitLength() > other.BigitLength()) {


    ASSERT(other.bigits_[other.used_digits_ - 1] >= ((1 << kBigitSize) / 16));


    result += bigits_[used_digits_ - 1];
    SubtractTimes(other, bigits_[used_digits_ - 1]);
  }

  ASSERT(BigitLength() == other.BigitLength());


  Chunk this_bigit = bigits_[used_digits_ - 1];
  Chunk other_bigit = other.bigits_[other.used_digits_ - 1];

  if (other.used_digits_ == 1) {

    int quotient = this_bigit / other_bigit;
    bigits_[used_digits_ - 1] = this_bigit - other_bigit * quotient;
    result += quotient;
    Clamp();
    return result;
  }

  int division_estimate = this_bigit / (other_bigit + 1);
  result += division_estimate;
  SubtractTimes(other, division_estimate);

  if (other_bigit * (division_estimate + 1) > this_bigit) {


    return result;
  }

  while (LessEqual(other, *this)) {
    SubtractBignum(other);
    result++;
  }
  return result;
}
