whichFPReturnVariant(Type *T) {
  switch (T->getTypeID()) {
  case Type::FloatTyID:
    return FRet;
  case Type::DoubleTyID:
    return DRet;
  case Type::StructTyID:
    if (T->getStructNumElements() != 2)
      break;
    if ((T->getContainedType(0)->isFloatTy()) &&
        (T->getContainedType(1)->isFloatTy()))
      return CFRet;
    if ((T->getContainedType(0)->isDoubleTy()) &&
        (T->getContainedType(1)->isDoubleTy()))
      return CDRet;
    break;
  default:
    break;
  }
  return NoFPRet;
}
