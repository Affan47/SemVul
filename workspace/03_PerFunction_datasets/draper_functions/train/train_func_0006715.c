LLVMGetGC(LLVMValueRef Fn) {
  Function *F = unwrap<Function>(Fn);
  return F->hasGC()? F->getGC() : 0;
}
