InitialScaledStartValues(uint64_t significand,
                                     int exponent,
                                     bool lower_boundary_is_closer,
                                     int estimated_power,
                                     bool need_boundary_deltas,
                                     Bignum* numerator,
                                     Bignum* denominator,
                                     Bignum* delta_minus,
                                     Bignum* delta_plus) {
  if (exponent >= 0) {
    InitialScaledStartValuesPositiveExponent(
        significand, exponent, estimated_power, need_boundary_deltas,
        numerator, denominator, delta_minus, delta_plus);
  } else if (estimated_power >= 0) {
    InitialScaledStartValuesNegativeExponentPositivePower(
        significand, exponent, estimated_power, need_boundary_deltas,
        numerator, denominator, delta_minus, delta_plus);
  } else {
    InitialScaledStartValuesNegativeExponentNegativePower(
        significand, exponent, estimated_power, need_boundary_deltas,
        numerator, denominator, delta_minus, delta_plus);
  }

  if (need_boundary_deltas && lower_boundary_is_closer) {


    denominator->ShiftLeft(1);
    numerator->ShiftLeft(1);
    delta_plus->ShiftLeft(1);
  }
}
