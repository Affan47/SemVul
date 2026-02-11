isTypeLegal(const Type *Ty, EVT &VT, bool AllowI1) {
  VT = TLI.getValueType(Ty, true);
  if (VT == MVT::Other || !VT.isSimple())

    return false;


  if (VT == MVT::f64 && !X86ScalarSSEf64)
     return false;
  if (VT == MVT::f32 && !X86ScalarSSEf32)
     return false;

  if (VT == MVT::f80)
    return false;


  return (AllowI1 && VT == MVT::i1) || TLI.isTypeLegal(VT);
}
