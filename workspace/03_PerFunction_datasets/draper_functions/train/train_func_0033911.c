useSpillFunction(MachineFunction &MF,
      const CSIVect &CSI) const {
  if (shouldInlineCSR(MF, CSI))
    return false;
  unsigned NumCSI = CSI.size();
  if (NumCSI <= 1)
    return false;

  unsigned Threshold = isOptSize(MF) ? SpillFuncThresholdOs
                                     : SpillFuncThreshold;
  return Threshold < NumCSI;
}
