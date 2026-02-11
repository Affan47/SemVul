CriticalPathStep(const SUnit *SU) {
  const SDep *Next = 0;
  unsigned NextDepth = 0;

  if (SU != 0) {
    for (SUnit::const_pred_iterator P = SU->Preds.begin(), PE = SU->Preds.end();
         P != PE; ++P) {
      const SUnit *PredSU = P->getSUnit();
      unsigned PredLatency = P->getLatency();
      unsigned PredTotalLatency = PredSU->getDepth() + PredLatency;


      if (NextDepth < PredTotalLatency ||
          (NextDepth == PredTotalLatency && P->getKind() == SDep::Anti)) {
        NextDepth = PredTotalLatency;
        Next = &*P;
      }
    }
  }

  return (Next) ? Next->getSUnit() : 0;
}
