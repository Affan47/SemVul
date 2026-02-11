getSignedMax() const {
  APInt SignedMax(APInt::getSignedMaxValue(getBitWidth()));
  if (!isWrappedSet()) {
    if (getLower().sle(getUpper() - 1))
      return getUpper() - 1;
    return SignedMax;
  }
  if (getLower().isNegative() == getUpper().isNegative())
    return SignedMax;
  return getUpper() - 1;
}
