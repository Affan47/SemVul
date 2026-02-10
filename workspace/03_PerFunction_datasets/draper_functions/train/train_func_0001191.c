isAssociativeAndCommutative(const MachineInstr &Inst) const {
  switch (Inst.getOpcode()) {
  case X86::AND8rr:
  case X86::AND16rr:
  case X86::AND32rr:
  case X86::AND64rr:
  case X86::OR8rr:
  case X86::OR16rr:
  case X86::OR32rr:
  case X86::OR64rr:
  case X86::XOR8rr:
  case X86::XOR16rr:
  case X86::XOR32rr:
  case X86::XOR64rr:
  case X86::IMUL16rr:
  case X86::IMUL32rr:
  case X86::IMUL64rr:
  case X86::PANDrr:
  case X86::PORrr:
  case X86::PXORrr:
  case X86::VPANDrr:
  case X86::VPANDYrr:
  case X86::VPORrr:
  case X86::VPORYrr:
  case X86::VPXORrr:
  case X86::VPXORYrr:


  case X86::MAXCPDrr:
  case X86::MAXCPSrr:
  case X86::MAXCSDrr:
  case X86::MAXCSSrr:
  case X86::MINCPDrr:
  case X86::MINCPSrr:
  case X86::MINCSDrr:
  case X86::MINCSSrr:
  case X86::VMAXCPDrr:
  case X86::VMAXCPSrr:
  case X86::VMAXCPDYrr:
  case X86::VMAXCPSYrr:
  case X86::VMAXCSDrr:
  case X86::VMAXCSSrr:
  case X86::VMINCPDrr:
  case X86::VMINCPSrr:
  case X86::VMINCPDYrr:
  case X86::VMINCPSYrr:
  case X86::VMINCSDrr:
  case X86::VMINCSSrr:
    return true;
  case X86::ADDPDrr:
  case X86::ADDPSrr:
  case X86::ADDSDrr:
  case X86::ADDSSrr:
  case X86::MULPDrr:
  case X86::MULPSrr:
  case X86::MULSDrr:
  case X86::MULSSrr:
  case X86::VADDPDrr:
  case X86::VADDPSrr:
  case X86::VADDPDYrr:
  case X86::VADDPSYrr:
  case X86::VADDSDrr:
  case X86::VADDSSrr:
  case X86::VMULPDrr:
  case X86::VMULPSrr:
  case X86::VMULPDYrr:
  case X86::VMULPSYrr:
  case X86::VMULSDrr:
  case X86::VMULSSrr:
    return Inst.getParent()->getParent()->getTarget().Options.UnsafeFPMath;
  default:
    return false;
  }
}
