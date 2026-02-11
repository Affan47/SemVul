CC_Sparc_Assign_f64(unsigned &ValNo, MVT &ValVT,
                                MVT &LocVT, CCValAssign::LocInfo &LocInfo,
                                ISD::ArgFlagsTy &ArgFlags, CCState &State)
{
  static const unsigned RegList[] = {
    SP::I0, SP::I1, SP::I2, SP::I3, SP::I4, SP::I5
  };

  if (unsigned Reg = State.AllocateReg(RegList, 6)) {
    State.addLoc(CCValAssign::getCustomReg(ValNo, ValVT, Reg, LocVT, LocInfo));
  } else {

    State.addLoc(CCValAssign::getCustomMem(ValNo, ValVT,
                                           State.AllocateStack(8,4),
                                           LocVT, LocInfo));
    return true;
  }


  if (unsigned Reg = State.AllocateReg(RegList, 6))
    State.addLoc(CCValAssign::getCustomReg(ValNo, ValVT, Reg, LocVT, LocInfo));
  else
    State.addLoc(CCValAssign::getCustomMem(ValNo, ValVT,
                                           State.AllocateStack(4,4),
                                           LocVT, LocInfo));
  return true;
}
