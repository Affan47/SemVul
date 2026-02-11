ConstantFoldBinaryFP(double (*NativeFP)(double, double),
                                      double V, double W, Type *Ty) {
  sys::llvm_fenv_clearexcept();
  V = NativeFP(V, W);
  if (sys::llvm_fenv_testexcept()) {
    sys::llvm_fenv_clearexcept();
    return 0;
  }

  if (Ty->isFloatTy())
    return ConstantFP::get(Ty->getContext(), APFloat((float)V));
  if (Ty->isDoubleTy())
    return ConstantFP::get(Ty->getContext(), APFloat(V));
  llvm_unreachable("Can only constant fold float/double");
  return 0;
}
