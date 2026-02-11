LLVMConstIntOfStringAndSize(LLVMTypeRef IntTy, const char Str[],
                                         unsigned SLen, uint8_t Radix) {
  return wrap(ConstantInt::get(unwrap<IntegerType>(IntTy), StringRef(Str, SLen),
                               Radix));
}
