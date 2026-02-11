handledStoreType(const MachineInstr *MI) {


  unsigned Opc = MI->getOpcode();
  switch (Opc) {
    case Hexagon::S4_storeirb_io:
    case Hexagon::S4_storeirh_io:
    case Hexagon::S4_storeiri_io:

      return MI->getOperand(0).isReg();
    default:
      return false;
  }
}
