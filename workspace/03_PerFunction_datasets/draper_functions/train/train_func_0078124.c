selectIntAddrMSA(SDValue Addr, SDValue &Base,
                                          SDValue &Offset) const {
  if (selectAddrRegImm10(Addr, Base, Offset))
    return true;

  if (selectAddrDefault(Addr, Base, Offset))
    return true;

  return false;
}
