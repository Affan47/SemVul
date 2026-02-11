ComputeGuess(Vector<const char> trimmed, int exponent,
                         double* guess) {
  if (trimmed.length() == 0) {
    *guess = 0.0;
    return true;
  }
  if (exponent + trimmed.length() - 1 >= kMaxDecimalPower) {
    *guess = Double::Infinity();
    return true;
  }
  if (exponent + trimmed.length() <= kMinDecimalPower) {
    *guess = 0.0;
    return true;
  }

  if (DoubleStrtod(trimmed, exponent, guess) ||
      DiyFpStrtod(trimmed, exponent, guess)) {
    return true;
  }
  if (*guess == Double::Infinity()) {
    return true;
  }
  return false;
}
