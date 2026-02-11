getEntryAlignment(const TargetData &TD) const {


  switch (getEntryKind()) {
  case MachineJumpTableInfo::EK_BlockAddress:
    return TD.getPointerABIAlignment();
  case MachineJumpTableInfo::EK_GPRel32BlockAddress:
  case MachineJumpTableInfo::EK_LabelDifference32:
  case MachineJumpTableInfo::EK_Custom32:
    return TD.getABIIntegerTypeAlignment(32);
  case MachineJumpTableInfo::EK_Inline:
    return 1;
  }
  assert(0 && "Unknown jump table encoding!");
  return ~0;
}
