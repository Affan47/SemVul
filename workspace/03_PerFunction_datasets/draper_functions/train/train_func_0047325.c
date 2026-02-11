canClobberReachingPhysRegUse(const SUnit *DepSU, const SUnit *SU,
                                         ScheduleDAGRRList *scheduleDAG,
                                         const TargetInstrInfo *TII,
                                         const TargetRegisterInfo *TRI) {
  const unsigned *ImpDefs
    = TII->get(SU->getNode()->getMachineOpcode()).getImplicitDefs();
  if(!ImpDefs)
    return false;

  for (SUnit::const_succ_iterator SI = SU->Succs.begin(), SE = SU->Succs.end();
       SI != SE; ++SI) {
    SUnit *SuccSU = SI->getSUnit();
    for (SUnit::const_pred_iterator PI = SuccSU->Preds.begin(),
           PE = SuccSU->Preds.end(); PI != PE; ++PI) {
      if (!PI->isAssignedRegDep())
        continue;

      for (const unsigned *ImpDef = ImpDefs; *ImpDef; ++ImpDef) {


        if (TRI->regsOverlap(*ImpDef, PI->getReg()) &&
            scheduleDAG->IsReachable(DepSU, PI->getSUnit()))
          return true;
      }
    }
  }
  return false;
}
