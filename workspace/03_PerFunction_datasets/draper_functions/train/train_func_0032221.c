extendDef(SlotIndex Idx, unsigned LocNo,
                          LiveRange *LR, const VNInfo *VNI,
                          SmallVectorImpl<SlotIndex> *Kills,
                          LiveIntervals &LIS, MachineDominatorTree &MDT,
                          UserValueScopes &UVS) {
  SmallVector<SlotIndex, 16> Todo;
  Todo.push_back(Idx);
  do {
    SlotIndex Start = Todo.pop_back_val();
    MachineBasicBlock *MBB = LIS.getMBBFromIndex(Start);
    SlotIndex Stop = LIS.getMBBEndIdx(MBB);
    LocMap::iterator I = locInts.find(Start);


    bool ToEnd = true;
    if (LR && VNI) {
      LiveInterval::Segment *Segment = LR->getSegmentContaining(Start);
      if (!Segment || Segment->valno != VNI) {
        if (Kills)
          Kills->push_back(Start);
        continue;
      }
      if (Segment->end < Stop)
        Stop = Segment->end, ToEnd = false;
    }


    if (I.valid() && I.start() <= Start) {

      Start = Start.getNextSlot();
      if (I.value() != LocNo || I.stop() != Start)
        continue;

      ++I;
    }


    if (I.valid() && I.start() < Stop)
      Stop = I.start(), ToEnd = false;

    else if (!ToEnd && Kills)
      Kills->push_back(Stop);

    if (Start >= Stop)
      continue;

    I.insert(Start, Stop, LocNo);


    if (!ToEnd)
      continue;
    const std::vector<MachineDomTreeNode*> &Children =
      MDT.getNode(MBB)->getChildren();
    for (unsigned i = 0, e = Children.size(); i != e; ++i) {
      MachineBasicBlock *MBB = Children[i]->getBlock();
      if (UVS.dominates(MBB))
        Todo.push_back(LIS.getMBBStartIdx(MBB));
    }
  } while (!Todo.empty());
}
