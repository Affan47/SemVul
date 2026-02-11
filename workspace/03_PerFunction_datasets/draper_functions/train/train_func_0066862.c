IsAnAddressOperand(const MachineOperand &MO) {


  switch (MO.getType()) {
  case MachineOperand::MO_Register:
  case MachineOperand::MO_Immediate:
  case MachineOperand::MO_CImmediate:
  case MachineOperand::MO_FPImmediate:
    return false;
  case MachineOperand::MO_MachineBasicBlock:
    return true;
  case MachineOperand::MO_FrameIndex:
    return false;
  case MachineOperand::MO_ConstantPoolIndex:
  case MachineOperand::MO_TargetIndex:
  case MachineOperand::MO_JumpTableIndex:
  case MachineOperand::MO_ExternalSymbol:
  case MachineOperand::MO_GlobalAddress:
  case MachineOperand::MO_BlockAddress:
    return true;
  case MachineOperand::MO_RegisterMask:
  case MachineOperand::MO_RegisterLiveOut:
    return false;
  case MachineOperand::MO_Metadata:
  case MachineOperand::MO_MCSymbol:
    return true;
  case MachineOperand::MO_CFIIndex:
    return false;
  }
  llvm_unreachable("unhandled machine operand type");
}
