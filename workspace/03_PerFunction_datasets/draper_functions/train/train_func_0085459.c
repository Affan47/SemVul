findMatch(const BitTracker::RegisterRef &Inp,
      BitTracker::RegisterRef &Out, const RegisterSet &AVs) {
  if (!BT.has(Inp.Reg))
    return false;
  const BitTracker::RegisterCell &InpRC = BT.lookup(Inp.Reg);
  unsigned B, W;
  if (!HBS::getSubregMask(Inp, B, W, MRI))
    return false;

  for (unsigned R = AVs.find_first(); R; R = AVs.find_next(R)) {
    if (!BT.has(R) || !HBS::isTransparentCopy(R, Inp, MRI))
      continue;
    const BitTracker::RegisterCell &RC = BT.lookup(R);
    unsigned RW = RC.width();
    if (W == RW) {
      if (MRI.getRegClass(Inp.Reg) != MRI.getRegClass(R))
        continue;
      if (!HBS::isEqual(InpRC, B, RC, 0, W))
        continue;
      Out.Reg = R;
      Out.Sub = 0;
      return true;
    }


    if (W*2 != RW)
      continue;
    if (MRI.getRegClass(R) != &Hexagon::DoubleRegsRegClass)
      continue;

    if (HBS::isEqual(InpRC, B, RC, 0, W))
      Out.Sub = Hexagon::subreg_loreg;
    else if (HBS::isEqual(InpRC, B, RC, W, W))
      Out.Sub = Hexagon::subreg_hireg;
    else
      continue;
    Out.Reg = R;
    return true;
  }
  return false;
}
