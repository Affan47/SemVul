isTypeLegal(Type *Ty, MVT &VT, bool AllowI1) {
  EVT evt = TLI.getValueType(Ty, true);
  if (evt == MVT::Other || !evt.isSimple())

    return false;

  VT = evt.getSimpleVT();


  if (VT == MVT::f64 && !X86ScalarSSEf64)
     return false;
  if (VT == MVT::f32 && !X86ScalarSSEf32)
     return false;

  if (VT == MVT::f80)
    return false;


  return (AllowI1 && VT == MVT::i1) || TLI.isTypeLegal(VT);
}
