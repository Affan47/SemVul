LLVMGetIntrinsicID(LLVMValueRef Fn) {
  if (Function *F = dyn_cast<Function>(unwrap(Fn)))
    return F->getIntrinsicID();
  return 0;
}
