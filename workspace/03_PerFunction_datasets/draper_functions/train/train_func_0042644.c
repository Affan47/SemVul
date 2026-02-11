pickTraceSucc(const MachineBasicBlock *MBB) {
  if (MBB->pred_empty())
    return nullptr;
  const MachineLoop *CurLoop = getLoopFor(MBB);
  const MachineBasicBlock *Best = nullptr;
  unsigned BestHeight = 0;
  for (const MachineBasicBlock *Succ : MBB->successors()) {

    if (CurLoop && Succ == CurLoop->getHeader())
      continue;

    if (isExitingLoop(CurLoop, getLoopFor(Succ)))
      continue;
    const MachineTraceMetrics::TraceBlockInfo *SuccTBI =
      getHeightResources(Succ);

    if (!SuccTBI)
      continue;

    unsigned Height = SuccTBI->InstrHeight;
    if (!Best || Height < BestHeight)
      Best = Succ, BestHeight = Height;
  }
  return Best;
}
