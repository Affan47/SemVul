MarkVirtRegAliveInBlock(VarInfo& VRInfo,
                                            MachineBasicBlock *DefBlock,
                                            MachineBasicBlock *MBB,
                                    std::vector<MachineBasicBlock*> &WorkList) {
  unsigned BBNum = MBB->getNumber();


  for (unsigned i = 0, e = VRInfo.Kills.size(); i != e; ++i)
    if (VRInfo.Kills[i]->getParent() == MBB) {
      VRInfo.Kills.erase(VRInfo.Kills.begin()+i);
      break;
    }

  if (MBB == DefBlock) return;

  if (VRInfo.AliveBlocks.test(BBNum))
    return;


  VRInfo.AliveBlocks.set(BBNum);

  WorkList.insert(WorkList.end(), MBB->pred_rbegin(), MBB->pred_rend());
}
