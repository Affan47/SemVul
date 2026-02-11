isSmallConstant(unsigned VR) const {
  const BitTracker::RegisterCell &RC = CMS->lookup(VR);
  uint16_t W = RC.width();
  if (W > 64)
    return false;
  uint64_t V = 0, B = 1;
  for (uint16_t i = 0; i < W; ++i) {
    const BitTracker::BitValue &BV = RC[i];
    if (BV.is(1))
      V |= B;
    else if (!BV.is(0))
      return false;
    B <<= 1;
  }


  if (W == 32)
    return isInt<16>(V);


  return isInt<8>(Lo_32(V)) && isInt<8>(Hi_32(V));
}
