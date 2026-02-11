ScheduledNode(SUnit *SU) {
  if (!TracksRegPressure)
    return;

  if (!SU->getNode())
    return;

  for (SUnit::pred_iterator I = SU->Preds.begin(), E = SU->Preds.end();
       I != E; ++I) {
    if (I->isCtrl())
      continue;
    SUnit *PredSU = I->getSUnit();


    if (PredSU->NumRegDefsLeft == 0) {
      continue;
    }


    --PredSU->NumRegDefsLeft;
    unsigned SkipRegDefs = PredSU->NumRegDefsLeft;
    for (ScheduleDAGSDNodes::RegDefIter RegDefPos(PredSU, scheduleDAG);
         RegDefPos.IsValid(); RegDefPos.Advance(), --SkipRegDefs) {
      if (SkipRegDefs)
        continue;

      unsigned RCId, Cost;
      GetCostForDef(RegDefPos, TLI, TII, TRI, RCId, Cost);
      RegPressure[RCId] += Cost;
      break;
    }
  }


  int SkipRegDefs = (int)SU->NumRegDefsLeft;
  for (ScheduleDAGSDNodes::RegDefIter RegDefPos(SU, scheduleDAG);
       RegDefPos.IsValid(); RegDefPos.Advance(), --SkipRegDefs) {
    if (SkipRegDefs > 0)
      continue;
    unsigned RCId, Cost;
    GetCostForDef(RegDefPos, TLI, TII, TRI, RCId, Cost);
    if (RegPressure[RCId] < Cost) {


      DEBUG(dbgs() << "  SU(" << SU->NodeNum << ") has too many regdefs\n");
      RegPressure[RCId] = 0;
    }
    else {
      RegPressure[RCId] -= Cost;
    }
  }
  dumpRegPressure();
}
