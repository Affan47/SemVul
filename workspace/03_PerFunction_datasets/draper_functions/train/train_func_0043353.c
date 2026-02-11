isLegalFlatAddressingMode(const AddrMode &AM) const {


  return AM.BaseOffs == 0 && (AM.Scale == 0 || AM.Scale == 1);
}
