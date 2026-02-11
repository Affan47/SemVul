isRunOfOnes(ConstantInt *Val, uint32_t &MB, uint32_t &ME) {
  const APInt& V = Val->getValue();
  uint32_t BitWidth = Val->getType()->getBitWidth();
  if (!APIntOps::isShiftedMask(BitWidth, V)) return false;


  MB = BitWidth - ((V - 1) ^ V).countLeadingZeros();

  ME = V.getActiveBits();
  return true;
}
