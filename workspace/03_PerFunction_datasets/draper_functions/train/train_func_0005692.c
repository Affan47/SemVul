ToggleKillFlag(MachineInstr *MI,
                                          MachineOperand &MO) {

  if (!MO.isKill()) {
    MO.setIsKill(true);
    return false;
  }


  if (KillIndices[MO.getReg()] != ~0u) {
    MO.setIsKill(false);
    return false;
  }


  MO.setIsKill(false);
  bool AllDead = true;
  const unsigned SuperReg = MO.getReg();
  for (const unsigned *Subreg = TRI->getSubRegisters(SuperReg);
       *Subreg; ++Subreg) {
    if (KillIndices[*Subreg] != ~0u) {
      MI->addOperand(MachineOperand::CreateReg(*Subreg,
                                               true  ,
                                               true  ,
                                               false ,
                                               false ));
      AllDead = false;
    }
  }

  if(AllDead)
    MO.setIsKill(true);
  return false;
}
