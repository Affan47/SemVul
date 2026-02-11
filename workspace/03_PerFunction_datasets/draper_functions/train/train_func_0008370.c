tryToFoldLoadIntoMI(MachineInstr *MI, unsigned OpNo,
                                      const LoadInst *LI) {

  MVT VT;
  if (!isLoadTypeLegal(LI->getType(), VT))
    return false;


  bool IsZExt = false;
  switch(MI->getOpcode()) {
    default:
      return false;

    case PPC::RLDICL:
    case PPC::RLDICL_32_64: {
      IsZExt = true;
      unsigned MB = MI->getOperand(3).getImm();
      if ((VT == MVT::i8 && MB <= 56) ||
          (VT == MVT::i16 && MB <= 48) ||
          (VT == MVT::i32 && MB <= 32))
        break;
      return false;
    }

    case PPC::RLWINM:
    case PPC::RLWINM8: {
      IsZExt = true;
      unsigned MB = MI->getOperand(3).getImm();
      if ((VT == MVT::i8 && MB <= 24) ||
          (VT == MVT::i16 && MB <= 16))
        break;
      return false;
    }

    case PPC::EXTSB:
    case PPC::EXTSB8:
    case PPC::EXTSB8_32_64:

      return false;

    case PPC::EXTSH:
    case PPC::EXTSH8:
    case PPC::EXTSH8_32_64: {
      if (VT != MVT::i16 && VT != MVT::i8)
        return false;
      break;
    }

    case PPC::EXTSW:
    case PPC::EXTSW_32_64: {
      if (VT != MVT::i32 && VT != MVT::i16 && VT != MVT::i8)
        return false;
      break;
    }
  }


  Address Addr;
  if (!PPCComputeAddress(LI->getOperand(0), Addr))
    return false;

  unsigned ResultReg = MI->getOperand(0).getReg();

  if (!PPCEmitLoad(VT, ResultReg, Addr, nullptr, IsZExt))
    return false;

  MI->eraseFromParent();
  return true;
}
