VerifyType(const Type *Ty) {
  if (!Types.insert(Ty)) return;

  Assert1(Context == &Ty->getContext(),
          "Type context does not match Module context!", Ty);

  switch (Ty->getTypeID()) {
  case Type::FunctionTyID: {
    const FunctionType *FTy = cast<FunctionType>(Ty);

    const Type *RetTy = FTy->getReturnType();
    Assert2(FunctionType::isValidReturnType(RetTy),
            "Function type with invalid return type", RetTy, FTy);
    VerifyType(RetTy);

    for (unsigned i = 0, e = FTy->getNumParams(); i != e; ++i) {
      const Type *ElTy = FTy->getParamType(i);
      Assert2(FunctionType::isValidArgumentType(ElTy),
              "Function type with invalid parameter type", ElTy, FTy);
      VerifyType(ElTy);
    }
    break;
  }
  case Type::StructTyID: {
    const StructType *STy = cast<StructType>(Ty);
    for (unsigned i = 0, e = STy->getNumElements(); i != e; ++i) {
      const Type *ElTy = STy->getElementType(i);
      Assert2(StructType::isValidElementType(ElTy),
              "Structure type with invalid element type", ElTy, STy);
      VerifyType(ElTy);
    }
    break;
  }
  case Type::ArrayTyID: {
    const ArrayType *ATy = cast<ArrayType>(Ty);
    Assert1(ArrayType::isValidElementType(ATy->getElementType()),
            "Array type with invalid element type", ATy);
    VerifyType(ATy->getElementType());
    break;
  }
  case Type::PointerTyID: {
    const PointerType *PTy = cast<PointerType>(Ty);
    Assert1(PointerType::isValidElementType(PTy->getElementType()),
            "Pointer type with invalid element type", PTy);
    VerifyType(PTy->getElementType());
    break;
  }
  case Type::VectorTyID: {
    const VectorType *VTy = cast<VectorType>(Ty);
    Assert1(VectorType::isValidElementType(VTy->getElementType()),
            "Vector type with invalid element type", VTy);
    VerifyType(VTy->getElementType());
    break;
  }
  default:
    break;
  }
}
