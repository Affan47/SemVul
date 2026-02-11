getPressureStateAt(const TargetRegisterClass *trc,
                                              SlotIndex i) const {
    if (trei.getPressureAtSlot(trc, i) == 0) {
      return Zero;
    } else if (trei.classOverCapacityAtSlot(trc, i)){
      return High;
    }
    return Low;
  }
