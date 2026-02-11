InitLLVM2SEHRegisterMapping(MCRegisterInfo *MRI) {

  for (unsigned Reg = X86::NoRegister+1; Reg < X86::NUM_TARGET_REGS; ++Reg) {
    int SEH = X86_MC::getX86RegNum(Reg);
    switch (Reg) {
    case X86::R8:  case X86::R8D:  case X86::R8W:  case X86::R8B:
    case X86::R9:  case X86::R9D:  case X86::R9W:  case X86::R9B:
    case X86::R10: case X86::R10D: case X86::R10W: case X86::R10B:
    case X86::R11: case X86::R11D: case X86::R11W: case X86::R11B:
    case X86::R12: case X86::R12D: case X86::R12W: case X86::R12B:
    case X86::R13: case X86::R13D: case X86::R13W: case X86::R13B:
    case X86::R14: case X86::R14D: case X86::R14W: case X86::R14B:
    case X86::R15: case X86::R15D: case X86::R15W: case X86::R15B:
    case X86::XMM8:  case X86::XMM9:  case X86::XMM10: case X86::XMM11:
    case X86::XMM12: case X86::XMM13: case X86::XMM14: case X86::XMM15:
    case X86::YMM8:  case X86::YMM9:  case X86::YMM10: case X86::YMM11:
    case X86::YMM12: case X86::YMM13: case X86::YMM14: case X86::YMM15:
      SEH += 8;
      break;
    }
    MRI->mapLLVMRegToSEHReg(Reg, SEH);
  }
}
