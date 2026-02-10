SwizzleInput(MachineInstr &MI,
    const std::vector<std::pair<unsigned, unsigned> > &RemapChan) const {
  unsigned Offset;
  if (TII->get(MI.getOpcode()).TSFlags & R600_InstFlag::TEX_INST)
    Offset = 2;
  else
    Offset = 3;
  for (unsigned i = 0; i < 4; i++) {
    unsigned Swizzle = MI.getOperand(i + Offset).getImm() + 1;
    for (unsigned j = 0, e = RemapChan.size(); j < e; j++) {
      if (RemapChan[j].first == Swizzle) {
        MI.getOperand(i + Offset).setImm(RemapChan[j].second - 1);
        break;
      }
    }
  }
}
