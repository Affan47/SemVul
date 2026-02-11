HandleByVal(unsigned ValNo, EVT ValVT,
                          EVT LocVT, CCValAssign::LocInfo LocInfo,
                          int MinSize, int MinAlign,
                          ISD::ArgFlagsTy ArgFlags) {
  unsigned Align = ArgFlags.getByValAlign();
  unsigned Size  = ArgFlags.getByValSize();
  if (MinSize > (int)Size)
    Size = MinSize;
  if (MinAlign > (int)Align)
    Align = MinAlign;
  unsigned Offset = AllocateStack(Size, Align);

  addLoc(CCValAssign::getMem(ValNo, ValVT, Offset, LocVT, LocInfo));
}
