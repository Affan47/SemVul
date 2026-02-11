binaryOr(const ConstantRange &Other) const {
  if (isEmptySet() || Other.isEmptySet())
    return ConstantRange(getBitWidth(), false);


  APInt umax = APIntOps::umax(getUnsignedMin(), Other.getUnsignedMin());
  if (umax.isMinValue())
    return ConstantRange(getBitWidth(), true);
  return ConstantRange(umax, APInt::getNullValue(getBitWidth()));
}
