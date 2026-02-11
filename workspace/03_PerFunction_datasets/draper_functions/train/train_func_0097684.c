getNullValue(const Type *Ty) {
  switch (Ty->getTypeID()) {
  case Type::IntegerTyID:
    return ConstantInt::get(Ty, 0);
  case Type::FloatTyID:
    return ConstantFP::get(Ty->getContext(), APFloat(APInt(32, 0)));
  case Type::DoubleTyID:
    return ConstantFP::get(Ty->getContext(), APFloat(APInt(64, 0)));
  case Type::X86_FP80TyID:
    return ConstantFP::get(Ty->getContext(), APFloat(APInt(80, 2, zero)));
  case Type::FP128TyID:
    return ConstantFP::get(Ty->getContext(),
                           APFloat(APInt(128, 2, zero), true));
  case Type::PPC_FP128TyID:
    return ConstantFP::get(Ty->getContext(), APFloat(APInt(128, 2, zero)));
  case Type::PointerTyID:
    return ConstantPointerNull::get(cast<PointerType>(Ty));
  case Type::StructTyID:
  case Type::ArrayTyID:
  case Type::VectorTyID:
    return ConstantAggregateZero::get(Ty);
  default:

    assert(!"Cannot create a null constant of that type!");
    return 0;
  }
}
