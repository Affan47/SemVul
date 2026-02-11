getName(MVT::SimpleValueType T) {
  switch (T) {
  case MVT::Other:   return "UNKNOWN";
  case MVT::iPTR:    return "TLI.getPointerTy()";
  case MVT::iPTRAny: return "TLI.getPointerTy()";
  default: return getEnumName(T);
  }
}
