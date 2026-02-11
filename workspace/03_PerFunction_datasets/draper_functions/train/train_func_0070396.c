addDef(SlotIndex Idx, const MachineOperand &LocMO) {

    LocMap::iterator I = locInts.find(Idx);
    if (!I.valid() || I.start() != Idx)
      I.insert(Idx, Idx.getNextSlot(), getLocationNo(LocMO));
    else

      I.setValue(getLocationNo(LocMO));
  }
