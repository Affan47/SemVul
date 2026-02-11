CheckFloat(Vector<const char> buffer,
                        int exponent,
                        float to_check) {
  DiyFp lower_boundary;
  DiyFp upper_boundary;
  Bignum input_digits;
  input_digits.AssignDecimalString(buffer);
  if (to_check == 0.0) {
    const float kMinFloat = 1e-45f;

    Single s(kMinFloat);
    s.NormalizedBoundaries(&lower_boundary, &upper_boundary);
    return CompareBignumToDiyFp(input_digits, exponent, lower_boundary) <= 0;
  }
  if (to_check == static_cast<float>(Double::Infinity())) {
    const float kMaxFloat = 3.4028234e38f;

    Single s(kMaxFloat);
    s.NormalizedBoundaries(&lower_boundary, &upper_boundary);
    return CompareBignumToDiyFp(input_digits, exponent, upper_boundary) >= 0;
  }
  Single s(to_check);
  s.NormalizedBoundaries(&lower_boundary, &upper_boundary);
  if ((s.Significand() & 1) == 0) {
    return CompareBignumToDiyFp(input_digits, exponent, lower_boundary) >= 0 &&
        CompareBignumToDiyFp(input_digits, exponent, upper_boundary) <= 0;
  } else {
    return CompareBignumToDiyFp(input_digits, exponent, lower_boundary) > 0 &&
        CompareBignumToDiyFp(input_digits, exponent, upper_boundary) < 0;
  }
}
