ComputeOperandLatency(SUnit *Def, SUnit *Use,
                                              SDep& dep) const {
  if (!InstrItins || InstrItins->isEmpty())
    return;


  if ((dep.getKind() != SDep::Data) || (dep.getReg() == 0))
    return;

  const unsigned Reg = dep.getReg();


  MachineInstr *DefMI = Def->getInstr();
  int DefIdx = DefMI->findRegisterDefOperandIdx(Reg);
  if (DefIdx != -1) {
    const MachineOperand &MO = DefMI->getOperand(DefIdx);
    if (MO.isReg() && MO.isImplicit() &&
        DefIdx >= (int)DefMI->getDesc().getNumOperands()) {


      DefIdx = DefMI->findRegisterDefOperandIdx(Reg, false, true, TRI);
    }
    MachineInstr *UseMI = Use->getInstr();

    int Latency = -1;
    if (UseMI) {
      for (unsigned i = 0, e = UseMI->getNumOperands(); i != e; ++i) {
        const MachineOperand &MO = UseMI->getOperand(i);
        if (!MO.isReg() || !MO.isUse())
          continue;
        unsigned MOReg = MO.getReg();
        if (MOReg != Reg)
          continue;

        int UseCycle = TII->getOperandLatency(InstrItins, DefMI, DefIdx,
                                              UseMI, i);
        Latency = std::max(Latency, UseCycle);
      }
    } else {

      if (!InstrItins || InstrItins->isEmpty())
        return;
      unsigned DefClass = DefMI->getDesc().getSchedClass();
      Latency = InstrItins->getOperandCycle(DefClass, DefIdx);
    }


    if (Latency >= 0)
      dep.setLatency(Latency);
  }
}
