getBottomBlock() {
  MachineBasicBlock *BotMBB = getHeader();
  MachineFunction::iterator End = BotMBB->getParent()->end();
  if (BotMBB != std::prev(End)) {
    MachineBasicBlock *NextMBB = &*std::next(BotMBB->getIterator());
    while (contains(NextMBB)) {
      BotMBB = NextMBB;
      if (BotMBB == &*std::next(BotMBB->getIterator()))
        break;
      NextMBB = &*std::next(BotMBB->getIterator());
    }
  }
  return BotMBB;
}
