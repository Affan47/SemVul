createHexagonMCAsmInfo(const MCRegisterInfo &MRI,
                                         const Triple &TT) {
  MCAsmInfo *MAI = new HexagonMCAsmInfo(TT);


  MCCFIInstruction Inst =
      MCCFIInstruction::createDefCfa(nullptr, Hexagon::R30, 0);
  MAI->addInitialFrameState(Inst);

  return MAI;
}
