LLVMGetMDKindIDInContext(LLVMContextRef C, const char* Name,
                                  unsigned SLen) {
  return unwrap(C)->getMDKindID(StringRef(Name, SLen));
}
