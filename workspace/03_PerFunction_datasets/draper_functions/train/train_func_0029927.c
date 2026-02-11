isLegalAddressingMode(const DataLayout &DL,
                                             const AddrMode &AM, Type *Ty,
                                             unsigned AS) const {

  if (AM.BaseGV)
    return false;

  switch (AS) {
  case AMDGPUAS::GLOBAL_ADDRESS: {
    if (Subtarget->getGeneration() >= AMDGPUSubtarget::VOLCANIC_ISLANDS) {


      return isLegalFlatAddressingMode(AM);
    }

    return isLegalMUBUFAddressingMode(AM);
  }
  case AMDGPUAS::CONSTANT_ADDRESS: {


    if (AM.BaseOffs % 4 != 0)
      return isLegalMUBUFAddressingMode(AM);


    if (DL.getTypeStoreSize(Ty) < 4)
      return isLegalMUBUFAddressingMode(AM);

    if (Subtarget->getGeneration() == AMDGPUSubtarget::SOUTHERN_ISLANDS) {

      if (!isUInt<8>(AM.BaseOffs / 4))
        return false;
    } else if (Subtarget->getGeneration() == AMDGPUSubtarget::SEA_ISLANDS) {


      if (!isUInt<32>(AM.BaseOffs / 4))
        return false;
    } else if (Subtarget->getGeneration() == AMDGPUSubtarget::VOLCANIC_ISLANDS) {

      if (!isUInt<20>(AM.BaseOffs))
        return false;
    } else
      llvm_unreachable("unhandled generation");

    if (AM.Scale == 0)
      return true;

    if (AM.Scale == 1 && AM.HasBaseReg)
      return true;

    return false;
  }

  case AMDGPUAS::PRIVATE_ADDRESS:
  case AMDGPUAS::UNKNOWN_ADDRESS_SPACE:
    return isLegalMUBUFAddressingMode(AM);

  case AMDGPUAS::LOCAL_ADDRESS:
  case AMDGPUAS::REGION_ADDRESS: {


    if (!isUInt<16>(AM.BaseOffs))
      return false;

    if (AM.Scale == 0)
      return true;

    if (AM.Scale == 1 && AM.HasBaseReg)
      return true;

    return false;
  }
  case AMDGPUAS::FLAT_ADDRESS:
    return isLegalFlatAddressingMode(AM);

  default:
    llvm_unreachable("unhandled address space");
  }
}
