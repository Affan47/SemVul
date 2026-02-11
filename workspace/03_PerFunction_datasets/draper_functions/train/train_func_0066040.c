pickTracePred(const MachineBasicBlock *MBB) {
  if (MBB->pred_empty())
    return nullptr;
  const MachineLoop *CurLoop = getLoopFor(MBB);

  if (CurLoop && MBB == CurLoop->getHeader())
    return nullptr;
  unsigned CurCount = MTM.getResources(MBB)->InstrCount;
  const MachineBasicBlock *Best = nullptr;
  unsigned BestDepth = 0;
  for (const MachineBasicBlock *Pred : MBB->predecessors()) {
    const MachineTraceMetrics::TraceBlockInfo *PredTBI =
      getDepthResources(Pred);

    if (!PredTBI)
      continue;

    unsigned Depth = PredTBI->InstrDepth + CurCount;
    if (!Best || Depth < BestDepth)
      Best = Pred, BestDepth = Depth;
  }
  return Best;
}
