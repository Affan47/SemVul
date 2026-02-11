MatchAddressBase(SDValue N, X86ISelAddressMode &AM) {

  if (AM.BaseType != X86ISelAddressMode::RegBase || AM.Base_Reg.getNode()) {

    if (AM.IndexReg.getNode() == 0) {
      AM.IndexReg = N;
      AM.Scale = 1;
      return false;
    }


    return true;
  }


  AM.BaseType = X86ISelAddressMode::RegBase;
  AM.Base_Reg = N;
  return false;
}
