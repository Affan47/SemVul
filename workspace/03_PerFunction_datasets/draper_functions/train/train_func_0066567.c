addAvailable(int SlotOrReMat, unsigned Reg, bool CanClobber = true) {


    ModifyStackSlotOrReMat(SlotOrReMat);

    PhysRegsAvailable.insert(std::make_pair(Reg, SlotOrReMat));
    SpillSlotsOrReMatsAvailable[SlotOrReMat]= (Reg << 1) |
                                              (unsigned)CanClobber;

    if (SlotOrReMat > VirtRegMap::MAX_STACK_SLOT)
      DEBUG(dbgs() << "Remembering RM#"
                   << SlotOrReMat-VirtRegMap::MAX_STACK_SLOT-1);
    else
      DEBUG(dbgs() << "Remembering SS#" << SlotOrReMat);
    DEBUG(dbgs() << " in physreg " << TRI->getName(Reg) << "\n");
  }
