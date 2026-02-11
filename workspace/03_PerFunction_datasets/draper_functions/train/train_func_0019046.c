expandInstr(MachineBasicBlock &MBB, Iter I) {
  switch(I->getOpcode()) {
  case Mips::LOAD_CCOND_DSP:
    expandLoadCCond(MBB, I);
    break;
  case Mips::STORE_CCOND_DSP:
    expandStoreCCond(MBB, I);
    break;
  case Mips::LOAD_ACC64:
  case Mips::LOAD_ACC64DSP:
    expandLoadACC(MBB, I, 4);
    break;
  case Mips::LOAD_ACC128:
    expandLoadACC(MBB, I, 8);
    break;
  case Mips::STORE_ACC64:
    expandStoreACC(MBB, I, Mips::PseudoMFHI, Mips::PseudoMFLO, 4);
    break;
  case Mips::STORE_ACC64DSP:
    expandStoreACC(MBB, I, Mips::MFHI_DSP, Mips::MFLO_DSP, 4);
    break;
  case Mips::STORE_ACC128:
    expandStoreACC(MBB, I, Mips::PseudoMFHI64, Mips::PseudoMFLO64, 8);
    break;
  case Mips::BuildPairF64:
    if (expandBuildPairF64(MBB, I, false))
      MBB.erase(I);
    return false;
  case Mips::BuildPairF64_64:
    if (expandBuildPairF64(MBB, I, true))
      MBB.erase(I);
    return false;
  case Mips::ExtractElementF64:
    if (expandExtractElementF64(MBB, I, false))
      MBB.erase(I);
    return false;
  case Mips::ExtractElementF64_64:
    if (expandExtractElementF64(MBB, I, true))
      MBB.erase(I);
    return false;
  case TargetOpcode::COPY:
    if (!expandCopy(MBB, I))
      return false;
    break;
  default:
    return false;
  }

  MBB.erase(I);
  return true;
}
