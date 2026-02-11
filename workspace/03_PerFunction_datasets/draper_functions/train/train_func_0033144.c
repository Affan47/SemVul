ComputeLatency(SUnit *SU) {
  const InstrItineraryData &InstrItins = TM.getInstrItineraryData();


  SU->Latency =
    InstrItins.getStageLatency(SU->getInstr()->getDesc().getSchedClass());


  if (InstrItins.isEmpty())
    if (SU->getInstr()->getDesc().mayLoad())
      SU->Latency += 2;
}
