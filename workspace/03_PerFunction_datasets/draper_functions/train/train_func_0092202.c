CC_Hexagon (unsigned ValNo, MVT ValVT,
            MVT LocVT, CCValAssign::LocInfo LocInfo,
            ISD::ArgFlagsTy ArgFlags, CCState &State) {

  if (ArgFlags.isByVal()) {

    unsigned Offset = State.AllocateStack(ArgFlags.getByValSize(),
                                          ArgFlags.getByValAlign());
    State.addLoc(CCValAssign::getMem(ValNo, ValVT, Offset, LocVT, LocInfo));
    return false;
  }

  if (LocVT == MVT::i1 || LocVT == MVT::i8 || LocVT == MVT::i16) {
    LocVT = MVT::i32;
    ValVT = MVT::i32;
    if (ArgFlags.isSExt())
      LocInfo = CCValAssign::SExt;
    else if (ArgFlags.isZExt())
      LocInfo = CCValAssign::ZExt;
    else
      LocInfo = CCValAssign::AExt;
  } else if (LocVT == MVT::v4i8 || LocVT == MVT::v2i16) {
    LocVT = MVT::i32;
    LocInfo = CCValAssign::BCvt;
  } else if (LocVT == MVT::v8i8 || LocVT == MVT::v4i16 || LocVT == MVT::v2i32) {
    LocVT = MVT::i64;
    LocInfo = CCValAssign::BCvt;
  }

  if (LocVT == MVT::i32 || LocVT == MVT::f32) {
    if (!CC_Hexagon32(ValNo, ValVT, LocVT, LocInfo, ArgFlags, State))
      return false;
  }

  if (LocVT == MVT::i64 || LocVT == MVT::f64) {
    if (!CC_Hexagon64(ValNo, ValVT, LocVT, LocInfo, ArgFlags, State))
      return false;
  }

  return true;
}
