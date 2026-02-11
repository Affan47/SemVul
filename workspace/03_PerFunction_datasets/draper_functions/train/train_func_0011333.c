canLosslesslyBitCastTo(Type *Ty) const {

  if (this == Ty)
    return true;


  if (!this->isFirstClassType() || !Ty->isFirstClassType())
    return false;


  if (const VectorType *thisPTy = dyn_cast<VectorType>(this)) {
    if (const VectorType *thatPTy = dyn_cast<VectorType>(Ty))
      return thisPTy->getBitWidth() == thatPTy->getBitWidth();
    if (Ty->getTypeID() == Type::X86_MMXTyID &&
        thisPTy->getBitWidth() == 64)
      return true;
  }

  if (this->getTypeID() == Type::X86_MMXTyID)
    if (const VectorType *thatPTy = dyn_cast<VectorType>(Ty))
      if (thatPTy->getBitWidth() == 64)
        return true;


  if (this->isPointerTy())
    return Ty->isPointerTy();
  return false;
}
