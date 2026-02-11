ToShortestIeeeNumber(
    double value,
    StringBuilder* result_builder,
    DoubleToStringConverter::DtoaMode mode) const {
  ASSERT(mode == SHORTEST || mode == SHORTEST_SINGLE);
  if (Double(value).IsSpecial()) {
    return HandleSpecialValues(value, result_builder);
  }

  int decimal_point;
  bool sign;
  const int kDecimalRepCapacity = kBase10MaximalLength + 1;
  char decimal_rep[kDecimalRepCapacity];
  int decimal_rep_length;

  DoubleToAscii(value, mode, 0, decimal_rep, kDecimalRepCapacity,
                &sign, &decimal_rep_length, &decimal_point);

  bool unique_zero = (flags_ & UNIQUE_ZERO) != 0;
  if (sign && (value != 0.0 || !unique_zero)) {
    result_builder->AddCharacter('-');
  }

  int exponent = decimal_point - 1;
  if ((decimal_in_shortest_low_ <= exponent) &&
      (exponent < decimal_in_shortest_high_)) {
    CreateDecimalRepresentation(decimal_rep, decimal_rep_length,
                                decimal_point,
                                Max(0, decimal_rep_length - decimal_point),
                                result_builder);
  } else {
    CreateExponentialRepresentation(decimal_rep, decimal_rep_length, exponent,
                                    result_builder);
  }
  return true;
}
