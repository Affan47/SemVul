hasHighOperandLatency(const TargetSchedModel &SchedModel,
                      const MachineRegisterInfo *MRI,
                      const MachineInstr *DefMI, unsigned DefIdx,
                      const MachineInstr *UseMI, unsigned UseIdx) const {
  unsigned DDomain = DefMI->getDesc().TSFlags & ARMII::DomainMask;
  unsigned UDomain = UseMI->getDesc().TSFlags & ARMII::DomainMask;
  if (Subtarget.isCortexA8() &&
      (DDomain == ARMII::DomainVFP || UDomain == ARMII::DomainVFP))

    return true;


  unsigned Latency
    = SchedModel.computeOperandLatency(DefMI, DefIdx, UseMI, UseIdx);
  if (Latency <= 3)
    return false;
  return DDomain == ARMII::DomainVFP || DDomain == ARMII::DomainNEON ||
         UDomain == ARMII::DomainVFP || UDomain == ARMII::DomainNEON;
}
