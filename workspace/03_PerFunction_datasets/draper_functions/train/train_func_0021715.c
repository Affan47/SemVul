get(const Type* Ty, double V) {
  LLVMContext &Context = Ty->getContext();

  APFloat FV(V);
  bool ignored;
  FV.convert(*TypeToFloatSemantics(Ty->getScalarType()),
             APFloat::rmNearestTiesToEven, &ignored);
  Constant *C = get(Context, FV);


  if (const VectorType *VTy = dyn_cast<VectorType>(Ty))
    return ConstantVector::get(
      std::vector<Constant *>(VTy->getNumElements(), C));

  return C;
}
