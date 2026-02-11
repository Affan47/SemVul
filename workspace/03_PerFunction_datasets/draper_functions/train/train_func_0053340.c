findRepresentativeClass(const TargetRegisterInfo *TRI,
                                            MVT VT) const {
  const TargetRegisterClass *RC = RegClassForVT[VT.SimpleTy];
  if (!RC)
    return std::make_pair(RC, 0);


  BitVector SuperRegRC(TRI->getNumRegClasses());
  for (SuperRegClassIterator RCI(RC, TRI); RCI.isValid(); ++RCI)
    SuperRegRC.setBitsInMask(RCI.getMask());


  const TargetRegisterClass *BestRC = RC;
  for (int i = SuperRegRC.find_first(); i >= 0; i = SuperRegRC.find_next(i)) {
    const TargetRegisterClass *SuperRC = TRI->getRegClass(i);

    if (SuperRC->getSize() <= BestRC->getSize())
      continue;
    if (!isLegalRC(SuperRC))
      continue;
    BestRC = SuperRC;
  }
  return std::make_pair(BestRC, 1);
}
