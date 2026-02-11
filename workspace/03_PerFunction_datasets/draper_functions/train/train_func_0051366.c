endPacket(MachineBasicBlock *MBB,
                                         MachineInstr *MI) {
  if (CurrentPacketMIs.size() > 1) {
    MachineInstr *MIFirst = CurrentPacketMIs.front();
    finalizeBundle(*MBB, MIFirst->getIterator(), MI->getIterator());
  }
  CurrentPacketMIs.clear();
  ResourceTracker->clearResources();
}
