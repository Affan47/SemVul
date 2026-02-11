canLosslesslyBitCastTo(Type *Ty) const {

  if (this == Ty)
    return true;


  if (!this->isFirstClassType() || !Ty->isFirstClassType())
    return false;


  if (auto *thisPTy = dyn_cast<VectorType>(this)) {
    if (auto *thatPTy = dyn_cast<VectorType>(Ty))
      return thisPTy->getBitWidth() == thatPTy->getBitWidth();
    if (Ty->getTypeID() == Type::X86_MMXTyID &&
        thisPTy->getBitWidth() == 64)
      return true;
  }

  if (this->getTypeID() == Type::X86_MMXTyID)
    if (auto *thatPTy = dyn_cast<VectorType>(Ty))
      if (thatPTy->getBitWidth() == 64)
        return true;


  if (auto *PTy = dyn_cast<PointerType>(this)) {
    if (auto *OtherPTy = dyn_cast<PointerType>(Ty))
      return PTy->getAddressSpace() == OtherPTy->getAddressSpace();
    return false;
  }
  return false;
}
