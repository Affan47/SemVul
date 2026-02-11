setExecutionCount(const MachineBasicBlock *MBB, double w) {
  DEBUG(dbgs() << "Creating Block " << MBB->getBasicBlock()->getName()
               << " (weight: " << format("%.20g",w) << ")\n");
  BlockInformation[MBB->getParent()][MBB] = w;
}
