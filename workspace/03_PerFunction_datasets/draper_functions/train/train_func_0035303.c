isLegalAddressingMode(const AddrMode &AM,
                                           const Type *Ty) const {


  if (AM.BaseOffs <= -(1LL << 16) || AM.BaseOffs >= (1LL << 16)-1)
    return false;


  if (AM.BaseGV)
    return false;


  switch (AM.Scale) {
  case 0:
    break;
  case 1:
    if (AM.HasBaseReg && AM.BaseOffs)
      return false;

    break;
  case 2:
    if (AM.HasBaseReg || AM.BaseOffs)
      return false;

    break;
  }

  return true;
}
