InitialScaledStartValuesNegativeExponentNegativePower(
    double v, int estimated_power, bool need_boundary_deltas,
    Bignum* numerator, Bignum* denominator,
    Bignum* delta_minus, Bignum* delta_plus) {
  const uint64_t kMinimalNormalizedExponent =
      V8_2PART_UINT64_C(0x00100000, 00000000);
  uint64_t significand = Double(v).Significand();
  int exponent = Double(v).Exponent();


  Bignum* power_ten = numerator;
  power_ten->AssignPowerUInt16(10, -estimated_power);

  if (need_boundary_deltas) {


    delta_plus->AssignBignum(*power_ten);
    delta_minus->AssignBignum(*power_ten);
  }


  ASSERT(numerator == power_ten);
  numerator->MultiplyByUInt64(significand);


  denominator->AssignUInt16(1);
  denominator->ShiftLeft(-exponent);

  if (need_boundary_deltas) {


    numerator->ShiftLeft(1);
    denominator->ShiftLeft(1);


    uint64_t v_bits = Double(v).AsUint64();
    if ((v_bits & Double::kSignificandMask) == 0 &&


        (v_bits & Double::kExponentMask) != kMinimalNormalizedExponent) {
      numerator->ShiftLeft(1);
      denominator->ShiftLeft(1);
      delta_plus->ShiftLeft(1);
    }
  }
}
