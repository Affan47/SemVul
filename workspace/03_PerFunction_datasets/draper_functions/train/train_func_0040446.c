initialize(ScheduleDAGMI *Dag) {
  DAG = Dag;
  SchedModel = DAG->getSchedModel();
  TRI = DAG->TRI;

  Rem.init(DAG, SchedModel);
  Top.init(DAG, SchedModel, &Rem);
  BotRoots.clear();


  const InstrItineraryData *Itin = SchedModel->getInstrItineraries();
  if (!Top.HazardRec) {
    Top.HazardRec =
        DAG->MF.getSubtarget().getInstrInfo()->CreateTargetMIHazardRecognizer(
            Itin, DAG);
  }
}
