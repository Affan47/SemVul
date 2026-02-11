commonChecksToProhibitNewValueJump(bool afterRA,
                          MachineBasicBlock::iterator MII) {


  if (MII->getDesc().mayStore())
    return false;


  if (MII->getOpcode() == Hexagon::J2_call)
    return false;


  if (!afterRA) {


    if (MII->getOpcode() == TargetOpcode::KILL ||
        MII->getOpcode() == TargetOpcode::PHI  ||
        MII->getOpcode() == TargetOpcode::COPY)
      return false;


    if (MII->getOpcode() == Hexagon::LDriw_pred     ||
        MII->getOpcode() == Hexagon::STriw_pred)
      return false;
  }

  return true;
}
