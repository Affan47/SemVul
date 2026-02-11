isLargeIntegerTy(bool Is32Bit, Type *Ty) {
  if (IntegerType *ITy = dyn_cast<IntegerType>(Ty))
    return ITy->getBitWidth() > (Is32Bit ? 32U : 64U);

  return false;
}
